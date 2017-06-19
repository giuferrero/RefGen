#include "class.hpp"

namespace PEAK{
    
/**************************************************************/
/* NAME :  Class Peak constructor */
/* DESCRIPTION :  */
/**************************************************************/
  
  Peak::Peak(const unsigned int lower, const unsigned int upper, const unsigned int th,const char* input,const char* output, const char* Chr) {
      
      this->lower = lower; 
      this->upper = upper;
      this->dim = upper - lower+1;
      this->th = th;
      try
      {
	count = new unsigned int [dim];
      }
      catch (...)
      {
	cerr << "Error:  It is not possible to allocate "<<dim*4<<" Bites of memory"<<endl; 
	throw;
      }
     for (unsigned int i=0; i<dim; i++)
       count[i]=0;
     inputName =string(input);
     outputName=string(output);
     this->Chr=string(Chr);
  }
    

/**************************************************************/
/* NAME :  Class Peak  destructor */
/* DESCRIPTION :  */
/**************************************************************/

Peak::~Peak(){
     
  if (count!=NULL) {
    delete[] count;
  }
  
 }   
 
 /**************************************************************/
/* NAME :  Class Peak Print */
/* DESCRIPTION :  it prints the class values*/
/**************************************************************/

 void Peak::Print()const {
   cout<<"Chr.: "<< Chr <<endl;
   cout<<"Lower: "<< lower <<endl;
   cout<<"Upper: "<< upper <<endl;
   cout<<"Input file: "<< inputName<<endl;
   cout<<"Output file: "<< outputName<<endl;
   for (unsigned int i=0; i<dim; i++)
     if (count[i]!=0)
      cout<<"count["<<i+lower<<"] = "<<count[i]<< endl;
 }

 /**************************************************************/
/* NAME :  Class Peak Read */
/* DESCRIPTION :  it  reads the input file*/
/**************************************************************/   
  
void Peak::Read(){
  
  ifstream in;
  char buffer[MAXSIZE];
  Parser parser;
  char delim[] = "\t ";
  in.open(inputName.c_str(),ifstream::in);
  if(!in) 
  {
    cerr << "\n*****Error opening input file "<<inputName<<" *****" << endl;
    throw;
    
  }
  unsigned int npeaks=0;
  while (!in.eof())
  {
    buffer[0]='\0';
    in.getline(buffer,MAXSIZE);
    npeaks++;
    if (npeaks%100000==0)
    {
      cout<<"Processed peaks: "<<npeaks<<endl;
    }
#if DEBUG    
    cout<<buffer<<endl;
#endif    
    parser.update(delim,buffer);
    if ((parser.size()==3) && (parser.get(0)==Chr))
    {
      
      if (atoi(parser.get(1).c_str())>atoi(parser.get(2).c_str()))
      {
	cout<<"\nError in peak: "<< npeaks<< "\n\n";
      }
      else
      {
	unsigned int l,u;
	if ((unsigned int) atoi(parser.get(1).c_str())<lower)
	  l=lower;
	else
	  l=(unsigned int)atoi(parser.get(1).c_str());
	if ((unsigned int)atoi(parser.get(2).c_str()) > upper)
	  u=upper;
	else
	  u=(unsigned int)atoi(parser.get(2).c_str());
	for (unsigned int i=l;i<=u && i>=lower && i<= upper; i++)
	{
	  count[i-lower]++;       
	}  
      }
   }
  }
 }

 /**************************************************************/
/* NAME :  Class Peak CheckPeak */
/* DESCRIPTION :  it identifies the peak according to the input threshold*/
/**************************************************************/   
 
 void Peak::CheckPeak(){
   
   unsigned int l=0;
   bool inPeak=false;
   ofstream out;
   out.open(outputName.c_str(),ofstream::out);
   if(!out) 
   {
    cerr << "\n*****Error opening output file "<<outputName<<" *****" << endl;
    throw;
   }
  
   for (unsigned int i=0; i<dim; i++)
   {
     if ((!inPeak)&&(count[i]>=th))
     {
       inPeak=true;
       l=i;
     }
     else
        if ((count[i]<th) && (inPeak))
	{
	  inPeak=false;
	  printPeak(l,i-1,out);
	}
    
     }
     if (inPeak)
        printPeak(l,dim-1,out);
   }
   

 /**************************************************************/
/* NAME :  Class Peak printPeak */
/* DESCRIPTION :  it  prints the peak position*/
/**************************************************************/   
 
 void Peak::printPeak(const unsigned int l, const unsigned int u, ofstream& out ){
  
#if DEBUG   
  cout<<Chr<<"\t"<<l+lower<<"\t"<<u+lower<<endl;
#endif  
  out<<Chr<<"\t"<<l+lower<<"\t"<<u+lower<<endl;
if (DIST){
  for (unsigned int i=l; i<=u; i++){
#if DEBUG    
    cout << count[i] << " ";
#endif    
    out << count[i] << " ";
  }
#if DEBUG   
  cout<<endl;
#endif 
  out<<endl;
 }
}
}
