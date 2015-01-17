/*------------------
if there is a buffered command, start executing it
------------------*/


void exe_actions(){
  if(buffered_action != NULL){
    spare = curAction;
    curAction = buffered_action;
    buffered_action = NULL;
    dispatch_action(*curAction);
  };
};


