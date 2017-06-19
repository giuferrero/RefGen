#include "class.hpp"

using namespace PEAK;

int main(int argc, char **argv) {
 
  
  time_t time_1,time_2;
  time(&time_1);
  
  cout<<"\n\n =========================================================\n";
  cout<<"|	                Count peaks                       |\n";
  cout<<" =========================================================\n";
  cout<<"\n If you find any bug, send an email to beccuti@di.unito.it\n";
  //It checks the number of its input parameters 

  if (argc<7)
	{
	std::cerr<<"\n\nUSE: RefGen <input_file> <output_file> <lower_bound> <upper_bound> <threshold> <Chromosome>\n\n";
	exit(EXIT_FAILURE);
	}
	
 unsigned int lower = atoi(argv[3]);
 unsigned int upper = atoi(argv[4]);
 unsigned int th = atoi(argv[5]);
 
 cout<<"\n\nSTARTING  EXECUTION ..."<<endl;
 try
 {
   Peak p(lower,upper,th,argv[1],argv[2],argv[6]);
   p.Read();
   p.CheckPeak();
 }
 catch (...)
 {
   std::cerr<<"Error using Peak class"<<endl<<endl;
   exit(EXIT_FAILURE);
 }
 time(&time_2);
 cout<<"\n\nEND EXECUTION"<<endl;
 cout<<"\n=========================== TIME ===========================\n\n\t";
 cout<<"Total time required: "<<(time_2-time_1)<<"s."<<endl;
 cout<<"\n=========================== TIME ===========================\n\n";
 return EXIT_SUCCESS;
}
