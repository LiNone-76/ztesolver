//
// Created by Salieri on 2023/11/25.
//
//#include <sstream>
//#include <signal.h>

#include "ZteModel.h"
#include "ZteSolver.h"
#include "tools.h"

// 主函数
int main(int argc, const char *argv[])
//int main_complete(int argc, const char *argv[])
{
    int returnCode = 0;
#ifdef CLP_DEBUG_MALLOC
    clp_memory(0);
#endif
#ifndef CBC_OTHER_SOLVER
    OsiClpSolverInterface solver1;
#if CLP_USE_OPENBLAS
    openblas_set_num_threads(CLP_USE_OPENBLAS);
#endif
#elif CBC_OTHER_SOLVER == 1
    OsiCpxSolverInterface solver1;
#endif
    ZteModel model(solver1);

    CbcParameters parameters;
#ifndef CBC_NO_INTERRUPT
    parameters.enableSignalHandler();
#endif
    // initialize
    ZteMain0(model, parameters);

    // define TEST_MESSAGE_HANDLER at top of file to check works on all messages
#ifdef TEST_MESSAGE_HANDLER
    test_message_handler(&model);
#endif
#ifdef CBC_DEBUG_EXTRA
    double startTime = CoinCpuTime();
  bool debugTuning = false;
#endif
    std::deque<std::string> inputQueue;

#ifdef CBC_DEBUG_EXTRA
    int n = argc;
    argc = 1;
    for (argc=1;argc<n;argc++) {
      if (!strcmp(argv[argc],"debugit"))
	break;
    }
    for (int i=0;i<MAX_INT_DEBUG;i++)
      cbc_int_debug[i] = -1;
    for (int i=0;i<MAX_DBL_DEBUG;i++)
      cbc_dbl_debug[i] = 0.0;
    if (argc<n) {
      // set debug stuff
      if (((n-argc)&1)==0) {
	printf("must be exact number of pairs\n");
	exit(77);
      }
      debugTuning = true;
      for (int i=argc+1;i<n;i+=2) {
	const char * name = argv[i];
	if (strstr(name,"int")) {
	  int k = name[3]-'0';
	  if (k<0||k>=MAX_INT_DEBUG) {
	    printf("bad debug field %s\n",name);
	    exit(77);
	  } else {
	    cbc_int_debug[k] = atoi(argv[i+1]);
	    printf("cbc_int_debug[%d] set to %d\n",k,cbc_int_debug[k]);
	  }
	} else if (strstr(name,"dbl")) {
	  int k = name[3]-'0';
	  if (k<0||k>=MAX_DBL_DEBUG) {
	    printf("bad debug field %s\n",name);
	    exit(77);
	  } else {
	    cbc_dbl_debug[k] = atof(argv[i+1]);
	    printf("cbc_dbl_debug[%d] set to %g\n",k,cbc_dbl_debug[k]);
	  }
	} else {
	  printf("unknown debug field %s\n",name);
	  exit(77);
	}
      }
    }
#endif
    // Put arguments into a queue.
    CoinParamUtils::formInputQueue(inputQueue, "cbc", argc, const_cast< char ** >(argv));
    returnCode = ZteMain1(inputQueue, model, parameters);
#ifdef CBC_DEBUG_EXTRA
    if (debugTuning) {
       printf("Run took %g seconds",CoinCpuTime()-startTime);
       for (int i=0;i<MAX_INT_DEBUG;i++) {
	 if (cbc_int_debug[i] != -1)
	   printf(" int%d value %d",i,cbc_int_debug[i]);
       }
       for (int i=0;i<MAX_DBL_DEBUG;i++) {
	 if (cbc_dbl_debug[i])
	   printf(" dbl%d value %g",i,cbc_dbl_debug[i]);
       }
       printf("\n");
     }
#endif

#ifdef CLP_DEBUG_MALLOC
    clp_memory(1);
#endif

    if (returnCode != 777) {
        return returnCode;
    } else {
        return 0;
    }
}