# Full grammar

statements -> statements statement
statement  ->   VECHUKO ( ID ) : // printing
              | VECHUKO ( STRING ) : // printing strings
              | expr SOLRAN ID SEIRAN:  // assignment of expr result to id
              | ORUVELA ( expr ) { statements } // if statement
              | ORUVELA ( expr ) { statements } ILLENA { statements }  //if else
              | NA statement VAATI SONNA statement VAATI SONNA MAARI statement { statements } // for loop
              | ID ( params ) { statements } // function definition
              | ITHU EPIDI IRUKU ID : // return statement
              | ID [] ( expr ) :
              ;
expr       ->   expr operator expr
              | expr comp expr
              | ( expr ) 
              | ID // variable
              | ID ( args ) // function call
              | ID [ expr ] // array
              ;