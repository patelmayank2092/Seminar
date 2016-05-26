 // $Id$
 /**

 * @file ./EDIT

 * @brief Definitions of Grid_int class  
 
 * @author Mayank, Sachin, Shivang, Vinayak 
 * @author Mat. No. : 22040622
 */
 
 
///
	/*@brief Grid_int Class Declarations in header file Grid_int.h. Grid generation and applying 
	 boundary conditions.*/
/// 	Class definitions in Grid_int.cpp




#include "Grid_int.h"
#include<omp.h>

///@brief Grid_int Constructor Definition.
Grid_int::Grid_int(int l_level)
{
level=l_level;
double elem = pow(2,level); 	///@param elem = number of elements (space between n grid points)///
ngp= (elem+1);
h=2.0/elem;			///@param h = Grid spacing.
X.resize(ngp*ngp,0);		///Stores intial approximation with BC

}


/////////////////////////////// To access private members //////////////////////////////////////////


polar polar_cor(double x,double y){
    polar p;
    double pi=3.141592653589793238;
        p.r = sqrt(x*x+y*y);
        if (std::signbit(x)==1 && std::signbit(y)==1) { p.phi = (atan(y/x) * 180 / pi)+180; }
        else if (std::signbit(x)==1 && std::signbit(y)==0) { p.phi = (atan(y/x) * 180 / pi)+180; }
        else if (std::signbit(x)==0 && std::signbit(y)==1) { p.phi = (atan(y/x) * 180 / pi); }
        else if (std::signbit(x)==0 && std::signbit(y)==0) { p.phi = (atan(y/x) * 180 / pi); }
        //p.phi = atan(y/x) * 180 / pi;


       return p;
}



///@return h = Grid spacing.
double Grid_int::get_hValue()
{
double temp =h;
return temp;
}

///@return ngp = number of grid points in one row.
double Grid_int::get_ngpValue()
{
double temp =ngp;
return temp;
}

/////////////////////////////// To access X vector /////////////////////////////////////////////////

///@return X= Vector which stores initial U
std::vector<double> Grid_int::get_Xvalue(){
std::vector<double> u = X;
return u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// To display X ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
 
void Grid_int::display_grid_int()
{ 
for(size_t i=0; i<ngp; ++i)
{
	{	
	for(size_t j=0; j<ngp;++j)
	std::cout<< X[i*ngp+j] << "\t";
	}
std::cout<<std::endl;
}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Functions to Apply Boundary conditions  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

///@brief function to apply boundary conditions 
///@param s= stores value of function sin(pi*x)*sinh(pi*y)
///@param h_= stores h value
///@param ngp_= stores ngp value



void Grid_int::boundary_con()
{

double pi=3.141592653589793238;
double s;
double h_=get_hValue();
double ngp_=get_ngpValue();
double phi = 0.0;


for(double y=-1,i=0; y<=1; y+=h_,i++)
{
    for(double x=-1,j=0; x<=1;x+=h_,j++)
    {
        /*if (std::signbit(x)==1) { phi = (atan(y/x) + pi)*0.5; }
        else   phi = atan(y/x) * 0.5;*/
        if (std::signbit(x)==1 && std::signbit(y)==1) { phi = (atan(y/x))+pi; }
        else if (std::signbit(x)==1 && std::signbit(y)==0) { phi = (atan(y/x))+pi; }
        else if (std::signbit(x)==0 && std::signbit(y)==1) { phi = (atan(y/x)) + 2*pi; }
        else if (std::signbit(x)==0 && std::signbit(y)==0) { phi = (atan(y/x)); }

        if(i==0 || i==ngp_-1) /// Traverses zero and n-1 row
			{
              
	    //s = pow((x*x+y*y),0.25)+sin(atan(y/x)*0.5);
        s = sqrt(sqrt(x*x+y*y))*sin(phi*0.5);
            //std::cout<<"loop i s= "<< s << " y= " << y << " x " << x <<" r value "<<p.r<<" phi value "<<p.phi<< std::endl;
            //std::cout << "i*ngp_+j " << i*ngp_+j<<std::endl;
			
            X[i*ngp_+j]=s; ///i*ngp_+j = maps 2D into 1D array X.
			}
        else if(j==0 || j==ngp_-1) ///Traverses zero and n-1 column
			{
                    s = sqrt(sqrt(x*x+y*y))*sin(phi*0.5);
             //s = pow((x*x+y*y),0.25)+sin(atan(y/x)*0.5);            
		//std::cout<<"loop j s= "<< s << " y= " << y << " x " << x <<" r value "<<p.r<<" phi value "<<p.phi<< std::endl;
            //std::cout << "i*ngp_+j " << i*ngp_+j<<std::endl;

			X[i*ngp_+j]=s;
			}
	}
}
}	



//------------------------------------------------------U_exact----------------------------------------------------------------//



std::vector<double> Grid_int::U_exact(){
double pi=3.141592653589793238;
double h_=get_hValue();
double ex=0.0;
double ngp_=get_ngpValue();
int i = 0;
std::vector<double> u_ex;
u_ex.resize(ngp_*ngp_,0.0);
double phi=0.0;



	for(double y=-1;y<=1;y+=h_){
	for(double x=-1;x<=1;x+=h_){
        /*if (std::signbit(x)==1) { phi = (atan(y/x) + pi)*0.5; }
        else  { phi = atan(y/x) * 0.5;}*/

        if (std::signbit(x)==1 && std::signbit(y)==1) { phi = (atan(y/x))+pi; }
        else if (std::signbit(x)==1 && std::signbit(y)==0) { phi = (atan(y/x))+pi; }
        else if (std::signbit(x)==0 && std::signbit(y)==1) { phi = (atan(y/x)) + 2*pi; }
        else if (std::signbit(x)==0 && std::signbit(y)==0) { phi = (atan(y/x)); }

                if (x==0 && y==0){ex = 0;}
                else{

                        ex = (sqrt(sqrt(x*x+y*y))*sin(phi*0.5));}
                        u_ex[i] = ex;
                        i++;
                  
	      }
	}	

return u_ex;

}












