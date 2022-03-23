include <stdio.h>
#include <stdlib.h>
#include <sysexits.h> 
#include <string.h> 
#include <errno.h>
#include <ctype.h>
#include "calendar.h"

/*
  This function initializes a Calendar structure based on the parameters provided. 
*/
int init_calendar(const char *name, int days,
                  int (*comp_func) (const void *ptr1, const void *ptr2),
                  void (*free_info_func) (void *ptr), Calendar ** calendar){
  Calendar *c;
  if (calendar &&  name  && days >= 1){
    c = malloc(sizeof(*c));
    if (c) {
   
      c->name = malloc(strlen(name)+1);
  
      if (c->name) {
	strcpy(c->name, name);
	c->days = days;
	c->comp_func = comp_func;
	c->free_info_func = free_info_func;
	c->events = calloc(days, sizeof (Event *));

	if(c->events){
	  c->total_events = 0;
  
	  *calendar = c;
  
	  return SUCCESS;
	}
      }
    }
  }
  return FAILURE;
}

/*
  This function prints, to the designated output stream, the calendar’s name,
  days, and total number of events if print all is true; otherwise this 
  information will not be printed. Information about each event (name, start
  time, and duration) will be printed regardless the value of print all. 
*/
int print_calendar(Calendar *calendar, FILE *output_stream, int print_all){
  Event *current;
  int  i;

  if(calendar &&  output_stream ){
    
    /* Header message */
    if(print_all){
      fprintf(output_stream, "Calendar's Name: \"%s\"\n", calendar->name);
      fprintf(output_stream, "Days: %d\n", calendar->days);
      fprintf(output_stream, "Total Events: %d\n", calendar->total_events);
      fprintf(output_stream, "\n");
    }

    /* Information about events */
    fprintf(output_stream, "**** Events ****\n");
  
    for(i = 0; i < calendar->days; i++ ){
      current = calendar->events[i];
      if(calendar->total_events > 0){
	fprintf(output_stream, "Day %d\n", i+1);
      }
      while(current != NULL){
	fprintf(output_stream, "Event's Name: \"%s\", Start_time: %d, Duration: %d\n",
		current->name, current->start_time, current->duration_minutes);
	current = current->next;
      }
    }
    return SUCCESS;
  }
  return FAILURE;
}

/*
  This function adds the speciﬁed event to the list associated 
  with the day parameter. 
*/
int add_event(Calendar *calendar, const char *name, int start_time,
              int duration_minutes, void *info, int day){
  Event *curr, *prev = NULL, *new_event, *checking;

  if(calendar &&  name && start_time >= 0 && start_time <= 2400
     && duration_minutes > 0 && day >= 1 && day <= calendar->days ){
   
    curr = calendar->events[day-1];

    /* function fails if event already exists */
    if(find_event(calendar, name, &checking) == FAILURE){
   
      /* Creating new event */
      new_event = malloc (sizeof(Event));
      if(new_event){
	
	new_event->name = malloc(strlen(name)+1);
	if(new_event->name){
	  
	  strcpy(new_event->name, name);
	  new_event->info = info;
	  new_event->start_time = start_time;
	  new_event->duration_minutes = duration_minutes;
	  new_event->next = NULL;

	  /* Add event if head is null */ 
	  if(!calendar->events[day-1]){
	    calendar->events[day-1] = new_event;
	  }

	  /* Otherwise, add event among existing events */
	  else{
	    while(curr){
	      if(calendar->comp_func(curr, new_event) >= 0){
		if( curr == calendar->events[day-1]){
		  new_event->next = calendar->events[day-1];
		  calendar->events[day-1] = new_event;
		}
		else {
		  new_event->next = curr;
		  prev->next = new_event;	
		}
		break;
	      }
	      else{
		prev = curr;
		curr = curr->next;
	      }
	    }
  
	    /* If the end is reached, the event must be added to the tail */
	    if(prev && !curr){
	      new_event->next = curr;
	      prev->next = new_event;
	    }
	  }
  
	  calendar->total_events++;
	  return SUCCESS;
	}
      }
    }
  }
  return FAILURE;
}

/*
  This function will return a pointer (via the out parameter event)
  to the event with the speciﬁedname (if any). 
*/
int find_event(Calendar *calendar, const char *name, Event **event){
  Event  *existing_event;
  int i;

  if(calendar &&  name && event){
  
    for(i = 0; i < calendar->days; i++){
      existing_event = calendar->events[i];
      while (existing_event) {
	if (strcmp(existing_event->name, name) == 0) {
	  *event = existing_event;
	  return SUCCESS;
	}
	existing_event = existing_event->next;
      }
    }
  }
  return FAILURE;
}

/*
  This function will return a pointer (via the out parameter event)
  to the event with the speciﬁed name in the speciﬁed day 
  (if such event exist). 
*/
int find_event_in_day(Calendar *calendar, const char *name, int day,
                      Event **event){
  Event  *existing_event;
  
  if(calendar &&  name && event && day >= 1 && day <= calendar->days){
 
    existing_event = calendar->events[day-1];

    while(existing_event != NULL){
      if(strcmp(existing_event->name, name) == 0){
	*event = existing_event;
	return SUCCESS;
      }
      existing_event = existing_event->next;
    }
  }
  return FAILURE;
}

/*
  This function will remove the speciﬁed event from the
  calendar returning any memory allocated for the event. 
*/
int remove_event(Calendar *calendar, const char *name){
  Event  *curr, *prev;
  int i;

  if(calendar &&  name){
  
    for(i = 0; i < calendar->days; i++){
      curr = calendar->events[i];

      while(curr){
	if(strcmp(curr->name, name) == 0){
	  /* removing at the head */
	  if(curr == calendar->events[i]){
	    calendar->events[i]=curr->next;  
	  }
	  /* removing anywhere else */
	  else{
	    prev->next = curr->next;
	  }

	  /* removing the actual event */
	  free(curr->name);
	  curr->name = NULL;
	  if (curr->info && calendar->free_info_func) {
	    calendar->free_info_func(curr->info);
	  }
	  free(curr);
	  curr = NULL;
	  
	  calendar->total_events--;
	  return SUCCESS;	
	}
	else {
	  prev = curr;
	  curr = curr->next;
	}
      }
    }
  }
  return FAILURE;
}

/*
  This function returns the info pointer associated with the speciﬁed 
  event. The function returns NULL if the event is not found. 
*/
void *get_event_info(Calendar *calendar, const char *name){
  Event  *existing_event;
  int i;

  for(i = 0; i < calendar->days; i++){
    
    existing_event= calendar->events[i];
    while (existing_event) {
      if(strcmp(existing_event->name, name) == 0){
	return existing_event->info;
      }
      existing_event= existing_event->next;
    }  
  }
  return NULL;
}

/*
  This function will remove all the event lists associated with
  the calendar and set them to empty lists.
*/ 
int clear_calendar(Calendar *calendar){
  int i;
  if (calendar){
  
    for(i = 0; i < calendar->days; i++){
      clear_day(calendar, i+1);
    }
    return SUCCESS;
  }
  return FAILURE;
}

/*
  This function will remove all the events for the speciﬁed 
  day setting the event list to empty. The total number of
  events will be adjusted accordingly. 
*/
int clear_day(Calendar *calendar, int day){
  Event *current;
  if (calendar && day >= 1 && day <= calendar->days){
  
    current = calendar->events[day-1]; 
    while(current){
      remove_event(calendar, current->name);
      current = calendar->events[day-1];
    }  
    return SUCCESS;
  }
  return FAILURE;
}

/*
  This function will return memory that was dynamically-allocated
  for the calendar. 
*/
int destroy_calendar(Calendar *calendar){
  
  if (calendar){
    
    free(calendar->name);
    calendar->name = NULL;
  
    clear_calendar(calendar);
  
    free(calendar->events);
    calendar->events = NULL;
  
    free(calendar);
    calendar = NULL;
    return SUCCESS;
  }
  return FAILURE;
}
