
#ifndef __IOS_H__
	#define __IOS_H__
	#include <iostream>
#endif 


#ifndef __STDL__
	#define __STDL__
	#include <stdlib.h>
#endif


#ifndef __STR_H__
	#define __STR_H__
	#include <string.h>

#endif


#ifndef __TIM_H__
	#define __TIM_H__
	#include <time.h>

#endif


#ifndef __FSTREAM__
	#define __FSTREAM__
	#include <fstream>
#endif

#ifndef __GEN_H__
	#define __GEN_H__
	#include "general.h"
#endif

#define DEBUG 0
#define DIST 0

namespace PEAK
{

  using namespace std;
  using namespace  general;
  
  const unsigned int MAXSIZE=1024;
  
  //! Class used to encode peak
  class Peak{
  //! it stores the frequency for each position
  unsigned int* count;
  //! it stores the lower position for which the frequencies are computed 
  unsigned  int lower;
   //! it stores the upper position for which the frequencies are computed 
  unsigned int upper;
  //! it stores the count size
  unsigned int dim;
  //! it stores the input file name
  string inputName;
  //! it stores the output file name
  string outputName;
  //! it stores the Chromosome Id
  string Chr;
  //! it stores the threshold used during the result analysis
  unsigned int th;
  public:
    
    //!Empty constructor 
    Peak(){count= NULL; dim=lower=upper=th=0; inputName=outputName=Chr="";};
    //!Constructor 
    Peak(const unsigned int lower, const unsigned int upper,const unsigned int th, const char* input,const char* output,const char* Chr);
    //!Read the input file
    void Read();
    //!Identify the peak positions
    void CheckPeak();
    //!Print the class values
    void Print()const;
    //!Destructor 
    ~Peak();
  private:
    void printPeak(const unsigned int l, const unsigned int u,ofstream& out); 
  };
  
};
