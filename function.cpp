#include "class.hpp"

namespace VAR_NAME{

/*************!
* "Peak" class constructor
* This method creates a peak object with given row, column, filename and
* number of files.
**************/	
	
	peak::peak(const int r, const int c, const int b, const string & n, const int num)
		{
		
		row = r;
		column = c;
		bin = b;
		input = n;
		n_file = num;
		
		if(row <= 0){
			cerr << "Row number is <=0" << endl;
			exit(EXIT_FAILURE);
		}
				
		else if(column <= 0){
			cerr << "Column number is <=0" << endl;
			exit(EXIT_FAILURE);
		}
		
		else if(n_file <= 0){
			cerr << "File number is <=0" << endl;
			exit(EXIT_FAILURE);
		}	
		
		count.resize (row);
		norm_count.resize (row);
		
		for(int i = 0; i < row; i++){
			
			count[i].resize(column);
			norm_count[i].resize(column);
			
			}
			
		}

/*************!
* Matrix read method
* This method reads an input matrix (peak x bins) by each value and 
* populates a new matrix named Count (bins x replicates).
**************/	

	void peak::read(){
		for(int i = 1; i <= n_file; i++){
			
			ostringstream of;
			
			of << input << i ;
			
			ifstream inf(of.str().c_str(),ifstream::in);
			
			if (!inf){
				
				cerr << "File input error" << endl;
				exit(EXIT_FAILURE);
				
				}
				
		int j = 0;
		int tmp;
		while(!inf.eof()){
			
			inf >> tmp;
			if (j<row)
				count[j][i-1] = tmp;
			j++;
			
		}
		
		inf.close();
		}
	

	}

/*************!
* Print method
* It prints out the newly created count matrix.
**************/	

	void peak::print(){
	
		for(int i = 0; i<row; i++){
			
			for(int j=0; j<column; j++){
				
				cout<<count[i][j]<<" ";
							
			}
			
			cout << endl;
			
		}
	
	}


/*************!
* Print method.
* It prints out the newly created normalized count matrix.
**************/	

	void peak::print_n(){
	
		cout.precision(13);
		
		for(int i = 0; i<row; i++){
			
			for(int j=0; j<column; j++){
				
				cout<<norm_count[i][j]<<" ";
							
			}
			
			cout << endl;
			
		}
	
	}

/*************!
* Row-wise geometric mean method
* This method computes the geometric mean of each matrix row and 
* populates a new matrix with the ratio between value and mean.
**************/	

	void peak::geo_mean(){
		
		for(int i = 0; i < row; i++){
			
			double result = 1.0;
			int temp = 0;
			
			// Row-wise geometric mean computation
			for(int j=0; j < column; j++){
				
				if (count[i][j] != 0){
					
					result = result * (count[i][j]);
					temp ++;
				
				}
				else {
				
					result = 0;
					
					break;
				}
			}
	
			if (result != 0){
			
				result = pow(result, 1.0 / temp);
			
			// Population of a new matrix with ratios between count and 
			// geometric mean
			
			
				for(int j=0; j < column; j++){
				
					norm_count[i][j] = (double) count[i][j] / result;
				}
			}
			else{
					
				for(int j=0; j < column; j++){
				
					norm_count[i][j] = 0.0;
				}
				
			}
			
		}
	}

/*************!
* Column-wise median
* This method computes the median of each column of a matrix and creates
* a new matrix norm_count dividing each count by the median.
**************/	

	void peak::col_med(){
		
		double median = 0;
		bool odd = false;
		cout.precision(13);
				
		vector < double > col_sort;
		
		for (int j=0; j < column; j++){	
			
			for(int i = 0; i < row; i++){
				
				if (norm_count[i][j] != 0){
				
					col_sort.push_back(norm_count[i][j]);
				   
				   }
			}
	
			sort(col_sort.begin(), col_sort.end());
			
			int row_c = col_sort.size();
			
			if (row_c % 2 == 0){
			
				odd = true;
			
			}
			
			if (odd){
				
				median = (col_sort[(row_c/2)-1] + col_sort[(row_c/2)])/ 2;

			}
			
			else{
				
				median = col_sort[row_c/2];

			}
			
			col_sort.clear();
			
		    for(int i = 0; i<row; i++){
				
				norm_count[i][j] = count[i][j] / median;
				
			}
			 
		}
	}

/*************!
* Inc count method
* Add a pseudocount to each element of the matrix of count
**************/	

	void peak::inc_count(){
	
		for(int i = 0; i < row; i++){
			
			for(int j=0; j < column; j++){
				
				count[i][j] = count[i][j] + 1;
				
			}
	
		}
	}

/*************!
* Output generation methos
* This method generates the output files in same format as input ones
**************/	

	void peak::write(){
		for(int n = 1; n <= n_file; n++){
			
			string n2 = static_cast<ostringstream*>( &(ostringstream() << n) )->str();
			
			string name = input + "_norm_" + n2;
			
			ofstream of;
			of.open(name);
			
			int count = 1;
			
			for (int i = 0; i < row; i++){

				if (count == bin){
					
					of << norm_count[i][n-1] << endl;
					count = 1;
					
				}
						
				else{
					
					count ++;
					of << norm_count[i][n-1] << "\t";
					
				}
			}
			
			of.close();	
		}
		
			
	}

}
