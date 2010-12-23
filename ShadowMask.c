#include <ShadowMask.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//pippo
const int NCOL=18;

/*
 *  CShadowAllocateRay(poolSource*,double*) purpose is to allocate correctly Ray.
 *  This piece of memory will be used by fortran routines, and shared with C.
 */
double* CShadowAllocateRay(poolSource* Src, double* Ray)
{
  Ray = (double*) realloc( Ray, 18*Src->NPOINT*sizeof(double) );
  return Ray;
}

/*
 *  CShadowPoolSourceLoad(poolSource*,char*) purpose is to read poolSource from a file.
 *  The fortran subroutine called takes advantages of gfile type.
 */
void CShadowPoolSourceLoad(poolSource* Src, char* FileIn)
{ 
  BindShadowPoolSourceLoad(Src,FileIn,strlen(FileIn));
}

/*
 *  CShadowPoolSourceWrite(poolSource*,char*) purpose is write poolSource from a file.
 *  The fortran subroutine called takes advantages of gfile type.
 */
void CShadowPoolSourceWrite(poolSource* Src, char* FileOut)
{ 
  BindShadowPoolSourceWrite(Src,FileOut,strlen(FileOut));
}

/*
 *  CShadowPoolOELoad(poolOE*,char*) purpose is read poolOE from a file.
 *  The fortran subroutine called takes advantages of gfile type.
 */
void CShadowPoolOELoad(poolOE* Oe, char* FileIn)
{
  BindShadowPoolOELoad(Oe,FileIn,strlen(FileIn));
}

/*
 *  CShadowPoolOEWrite(poolOE*,char*) purpose is read poolOE from a file.
 *  The fortran subroutine called takes advantages of gfile type.
 */
void CShadowPoolOEWrite(poolOE* Oe, char* FileOut)
{
  BindShadowPoolOEWrite(Oe,FileOut,strlen(FileOut));
}

/*
 *  CShadowSource1B(poolSource*,double*) purpose is to launch the new version
 *  of Source in shadow, bypassing reading/writing force steps.
 *  in the future version PoolSourceToGlobal(poolSource*) will be commented out.
 */
void CShadowSourceGeom(poolSource* Src, double* Ray)
{
  BindShadowSourceGeom(Src, Ray, &(Src->NPOINT));
}

void CShadowSourceSync(poolSource* Src, double* Ray)
{
  BindShadowSourceSync(Src, Ray, &(Src->NPOINT));
}

void CShadowTrace(poolOE* OE, double* Ray, int nPoint, int iCount)
{
  BindShadowTraceOE(OE,Ray,&nPoint,&iCount);
}

void CShadowGetDimRay(int* nCol, int* nPoint, char* FileDat)
{
  BindShadowGetDimRay(FileDat, strlen(FileDat), nPoint, nCol);
}

void CShadowReadRay(double* Ray, int nCol, int nPoint, char* FileDat)
{
  BindShadowReadRay(Ray, &nPoint, &nCol, FileDat, strlen(FileDat));
}


/*
 *  CShadowWriteRay(int,int,double*,char*) purpose is to write Ray in a binary file
 */
void CShadowWriteRay(int nCol, int nPoint, double* Ray, char* FileDat)
{
  BindShadowWriteRay(Ray, &nPoint, &nCol, FileDat, strlen(FileDat));
}

/*
 *  void CShadowFFresnel2D(double*, int, double, double_Complex*, int, double, double)
 *  purpose is to perform a 2D Fresnel image
 */

void CShadowFFresnel2D(double *ray, int nPoint, double dist, dComplex *image, pixel *x, pixel*z)
{
  BindShadowFFresnel2D(ray,&nPoint,&dist,image,x,z);
}



/*
 *   Initialize in a clever way;
 */

void CShadowSetupDefaultSource(poolSource* Src)
{
  memset(Src,'\0',sizeof(poolSource));
}

void CShadowSetupDefaultOE(poolOE* OE)
{
  memset(OE,'\0',sizeof(poolOE));
}


/*
 *   Initialize in a stupid way.
 */
/*
void CShadowSetupDefaultSource(poolSource* Src)
{
  Src->FDISTR =  2;
  Src->FGRID =  0;
  Src->FSOUR =  3;
  Src->FSOURCE_DEPTH =  1;
  Src->F_COHER =  0;
  Src->F_COLOR =  1;
  Src->F_PHOT =  0;
  Src->F_POL =  3;
  Src->F_POLAR =  0;
  Src->F_OPD =  1;
  Src->F_WIGGLER =  0;
  Src->F_BOUND_SOUR =  0;
  Src->F_SR_TYPE =  0;
  Src->ISTAR1 =  6775731;
  Src->NPOINT =  5000;
  Src->NCOL =  18;
  Src->N_CIRCLE =  0;
  Src->N_COLOR =  2;
  Src->N_CONE =  0;
  Src->IDO_VX =  1;
  Src->IDO_VZ =  1;
  Src->IDO_X_S =  1;
  Src->IDO_Y_S =  1;
  Src->IDO_Z_S =  1;
  Src->IDO_XL =  0;
  Src->IDO_XN =  0;
  Src->IDO_ZL =  0;
  Src->IDO_ZN =  0;
  Src->SIGXL1 =        0.00000000;
  Src->SIGXL2 =        0.00000000;
  Src->SIGXL3 =        0.00000000;
  Src->SIGXL4 =        0.00000000;
  Src->SIGXL5 =        0.00000000;
  Src->SIGXL6 =        0.00000000;
  Src->SIGXL7 =        0.00000000;
  Src->SIGXL8 =        0.00000000;
  Src->SIGXL9 =        0.00000000;
  Src->SIGXL10 =        0.00000000;
  Src->SIGZL1 =        0.00000000;
  Src->SIGZL2 =        0.00000000;
  Src->SIGZL3 =        0.00000000;
  Src->SIGZL4 =        0.00000000;
  Src->SIGZL5 =        0.00000000;
  Src->SIGZL6 =        0.00000000;
  Src->SIGZL7 =        0.00000000;
  Src->SIGZL8 =        0.00000000;
  Src->SIGZL9 =        0.00000000;
  Src->SIGZL10 =        0.00000000;
  Src->CONV_FACT =        0.00000000;
  Src->CONE_MAX =      0.0000000000;
  Src->CONE_MIN =        0.00000000;
  Src->EPSI_DX =        0.00000000;
  Src->EPSI_DZ =        0.00000000;
  Src->EPSI_X =        0.00000000;
  Src->EPSI_Z =        0.00000000;
  Src->HDIV1 =    5.00000000E-07;
  Src->HDIV2 =    5.00000000E-07;
  Src->PH1 =        1000.00000;
  Src->PH2 =        1010.0000;
  Src->PH3 =        0.00000000;
  Src->PH4 =        0.00000000;
  Src->PH5 =        0.00000000;
  Src->PH6 =        0.00000000;
  Src->PH7 =        0.00000000;
  Src->PH8 =        0.00000000;
  Src->PH9 =        0.00000000;
  Src->PH10 =        0.00000000;
  Src->RL1 =        0.00000000;
  Src->RL2 =        0.00000000;
  Src->RL3 =        0.00000000;
  Src->RL4 =        0.00000000;
  Src->RL5 =        0.00000000;
  Src->RL6 =        0.00000000;
  Src->RL7 =        0.00000000;
  Src->RL8 =        0.00000000;
  Src->RL9 =        0.00000000;
  Src->RL10 =        0.00000000;
  Src->BENER =        0.00000000;
  Src->POL_ANGLE =        0.00000000;
  Src->POL_DEG =        1.00000000;
  Src->R_ALADDIN =        0.00000000;
  Src->R_MAGNET =        0.00000000;
  Src->SIGDIX =     0.00100000000;
  Src->SIGDIZ =    0.000100000000;
  Src->SIGMAX =     0.00100000000;
  Src->SIGMAY =     0.00100000000;
  Src->SIGMAZ =     0.00100000000;
  Src->VDIV1 =    5.00000000E-06;
  Src->VDIV2 =    5.00000000E-06;
  Src->WXSOU =     0.10000000000;
  Src->WYSOU =     0.20000000000;
  Src->WZSOU =     0.20000000000;
  Src->PLASMA_ANGLE =        0.00000000;
  memset(Src->FILE_TRAJ,' ',1024);
  memset(Src->FILE_SOURCE,' ',1024);
  memset(Src->FILE_BOUND,' ',1024);
  Src->OE_NUMBER =  0;
  Src->IDUMMY =  0;
  Src->DUMMY =        0.00000000;
  Src->F_NEW =  0;
}
*/

