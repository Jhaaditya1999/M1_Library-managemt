# TEST PLAN:
## High level test plan
|Test ID|	Description|	Exp I/P|	Exp O/P|	Actual Out	|Type Of Test|
|-------|------------|---------|---------|--------------|------------|
|H_01	|Add book|	1234,"cs"|	1|	1	|Scenario based|
|H_02|	View book|	1234,"cs"	|1	|1	|Scenario based|
|H_03	|Search book|	1234	|1|	1|	Scenario based|
|H_04|	Update book	|1234, "issued", "16/04/21", "31/05/21", "Rahul","J", 900	|1	|1	|Scenario based|
|H_05|	Delete book	|1234	|1|	1|	Scenario based|
## Low level test plan
|Test ID|	Description|	Exp I/P|	Exp O/P|	Actual Out|	Type Of Test|
|-------|------------|---------|---------|------------|-------------|
|L_01|	Add the details of new book	|1234,"cs"|	1|	1	|Scenario based|
|L_02	|View the datails of all books|	1234 ,"cs"|	1|	1|	Scenario based|
|L_03|	Search the details of entered book by giving "ID" and "Name"|	1234|	1	|1	|Scenario based|
|L_04|	update the book status|	1234, "issued", "16/04/21", "31/05/21", "Rahul","J", 900|	1|	1	|Scenario based|
|L_05	|Delete the book by entering the "ID" of the book to delete|	1234|	1	|1	|Scenario base|
