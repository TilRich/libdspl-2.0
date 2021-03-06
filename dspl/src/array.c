/*
* Copyright (c) 2015-2020 Sergey Bakhurin
* Digital Signal Processing Library [http://dsplib.org]
*
* This file is part of libdspl-2.0.
*
* is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser  General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* DSPL is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dspl.h"
#include "blas.h"


/******************************************************************************
Vector linear transformation 
*******************************************************************************/
int array_scale_lin(double* x,   int n, 
    double xmin, double xmax, double dx,
    double h,    double* y)
{
  double kx;
  int k;  
  if(!x)
    return ERROR_PTR;
  if(n<1)
    return ERROR_SIZE;
  if(h<0.0)
    return ERROR_NEGATIVE;

  if(xmin >= xmax)
    return ERROR_MIN_MAX;

  kx = h / (xmax - xmin);

  for(k = 0; k < n; k++)
    y[k] = (x[k] - xmin) * kx + dx;

  return RES_OK;
}




/******************************************************************************
\fn int concat(void* a, size_t na, void* b, size_t nb, void* c) 
\brief
Concatenate arrays `a` and `b`

Let's arrays `a` and `b` are vectors: \n
`a = [a(0), a(1), ... a(na-1)]`,  \n
`b = [b(0), b(1), ... b(nb-1)]`,  \n
concatenation of these arrays will be array `c` size `na+nb`: \n
`c = [a(0), a(1), ... a(na-1), b(0), b(1), ... b(nb-1)]`.


\param[in]  a
Pointer to the first array `a`. \n
Array `a` size is `na` bytes. \n 
\n

\param[in]  na
Array `a` size (bytes). \n 
\n

\param[in]  b
Pointer to the second array `b`. \n
Array `b` size is `nb` bytes. \n 
\n

\param[in]  nb
Array `a` size (bytes). \n 
\n

\param[out] c
Pointer to the concatenation result array `c`. \n
Array `c` size is `na + nb` bytes. \n
Memory must be allocated. \n 
\n

\return
`RES_OK` if function returns successfully. \n
Else \ref ERROR_CODE_GROUP "code error".
 
Function uses pointer type `void*` and can be useful for an arrays 
concatenation with different types. \n
For example two `double` arrays concatenation:
\code{.cpp}
double a[3] = {1.0, 2.0, 3.0};
double b[2] = {4.0, 5.0};
double c[5];

concat((void*)a, 3*sizeof(double), (void*)b, 2*sizeof(double), (void*)c);
\endcode 
Vector `c` keeps follow data:
\verbatim
c = [1.0, 2.0, 3.0, 4.0, 5.0]
\endverbatim 

\author
Sergey Bakhurin
www.dsplib.org
*******************************************************************************/
int DSPL_API concat(void* a, size_t na, void* b, size_t nb, void* c)
{
  if(!a || !b || !c || c == b)
    return ERROR_PTR;
  if(na < 1 || nb < 1)
    return ERROR_SIZE;

  if(c != a)
    memcpy(c, a, na);

  memcpy((char*)c+na, b, nb);
  return RES_OK;
}





/******************************************************************************
\ingroup SPEC_MATH_COMMON_GROUP
\fn int decimate(double* x, int n, int d, double* y, int* cnt) 
\brief
Real vector decimation

Function `d` times decimates real vector `x`. \n
Output vector `y` keeps values corresponds to:
`y(k) = x(k*d), k = 0...n/d-1` \n

\param[in]  x
Pointer to the input real vector `x`. \n
Vector `x` size is `[n x 1]`. \n \n

\param[in]  n
Size of input vector `x`. \n \n

\param[in]  d
Decimation coefficient. \n
Each d-th vector will be copy from vector `x` to the 
output vector `y`. \n \n

\param[out] y
Pointer to the output decimated vector `y`. \n
Output vector size is `[n/d x 1]` will be copy 
to the address `cnt`. \n

\param[out] cnt
Address which will keep decimated vector `y` size. \n
Pointer can be `NULL`, vector `y` will not return 
in this case. \n \n

\return
`RES_OK` if function calculated successfully. \n
Else \ref ERROR_CODE_GROUP "code error".

Two-times decimation example:
\code{.cpp}
double x[10] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
double y[5];
int d = 2;
int cnt;

decimate(x, 10, d, y, &cnt);
\endcode 
As result variable `cnt` will be written value 5 and
vector `y` will keep  array:
\verbatim
c = [0.0, 2.0, 4.0, 6.0, 8.0]
\endverbatim 

\author
Sergey Bakhurin
www.dsplib.org
*******************************************************************************/
int DSPL_API decimate(double* x, int n, int d, double* y, int* cnt)
{
  int k = 0, i = 0;
  if(!x || !y)
    return ERROR_PTR;
  if(n < 1)
    return ERROR_SIZE;
  if(d < 1)
    return ERROR_NEGATIVE;

  k = i = 0;
  while(k + d <= n)
  {
    y[i] = x[k];
    k+=d;
    i++;
  }
  if(cnt)
    *cnt = i;

  return RES_OK;
}




/******************************************************************************
\ingroup SPEC_MATH_COMMON_GROUP
\fn int decimate_cmplx(complex_t* x, int n, int d, complex_t* y, int* cnt)
\brief
Complex vector decimation

Function `d` times decimates a complex vector `x`. \n
Output vector `y` keeps values corresponds to:
`y(k) = x(k*d), k = 0...n/d-1` \n

\param[in]  x
Pointer to the input complex vector `x`. \n
Vector `x` size is `[n x 1]`. \n \n

\param[in]  n
Size of input vector `x`. \n \n

\param[in]  d
Decimation coefficient. \n
Each d-th vector will be copy from vector `x` to the 
output vector `y`. \n \n

\param[out] y
Pointer to the output decimated vector `y`. \n
Output vector size is `[n/d x 1]` will be copy 
to the address `cnt`. \n
Memory must be allocated. \n \n

\param[out] cnt
Address which will keep decimated vector `y` size. \n
Pointer can be `NULL`, vector `y` will not return 
in this case. \n \n

\return
`RES_OK` if function calculated successfully. \n
Else \ref ERROR_CODE_GROUP "code error".

Two-times complex vector decimation example:

\code{.cpp}
compex_t x[10] = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}, {4.0, 4.0},
{5.0, 5.0}, {6.0, 6.0}, {7.0, 7.0}, {8.0, 8.0}, {9.0, 9.0}};
compex_t y[5];
int d = 2;
int cnt;

decimate_cmplx(x, 10, d, y, &cnt);
\endcode 

As result variable `cnt` will be written value 5 and
vector `y` will keep  array:

\verbatim
c = [0.0+0.0j, 2.0+2.0j, 4.0+4.0j, 6.0+6.0j, 8.0+8.0j]
\endverbatim

\author Sergey Bakhurin www.dsplib.org
*******************************************************************************/
int DSPL_API decimate_cmplx(complex_t* x, int n, int d, complex_t* y, int* cnt)
{
  int k = 0, i = 0;
  if(!x || !y)
    return ERROR_PTR;
  if(n < 1)
    return ERROR_SIZE;
  if(d < 1)
    return ERROR_NEGATIVE;

  k = i = 0;
  while(k + d < n)
  {
    RE(y[i]) = RE(x[k]);
    IM(y[i]) = IM(x[k]);
    k+=d;
    i++;
  }
  if(cnt)
    *cnt = i;

  return RES_OK;
}





/******************************************************************************
\ingroup SPEC_MATH_COMMON_GROUP
\fn int flipip(double* x, int n)
\brief
Flip real vector `x` in place

Function flips real vector `x` length `n` in the memory. \n
For example real vector `x`  length 6:\n
\verbatim
x = [0, 1, 2, 3, 4, 5]
\endverbatim
After flipping it will be as follow:
\verbatim
x = [5, 4, 3, 2, 1, 0]
\endverbatim

\param[in, out] x
Pointer to the real vector `x`. \n
Vector size is `[n x 1]`. \n
Flipped vector will be on the same address. \n
\n

\param[in] n
Length of the vector `x`. \n
\n

\return
`RES_OK` if function returns successfully. \n
 Else \ref ERROR_CODE_GROUP "error code".

Example:
\code{.cpp}
double x[5] = {0.0, 1.0, 2.0, 3.0, 4.0};
int i;  
for(i = 0; i < 5; i++)
  printf("%6.1f  ", x[i]);
flipip(x, 5);
printf("\n");
for(i = 0; i < 5; i++)
  printf("%6.1f  ", x[i]);
\endcode 
\n
Program result:
\verbatim
   0.0     1.0     2.0     3.0     4.0
   4.0     3.0     2.0     1.0     0.0
\endverbatim

\author Sergey Bakhurin www.dsplib.org
*******************************************************************************/
int DSPL_API flipip(double* x, int n)
{
  int k;
  double tmp;
  if(!x)
    return ERROR_PTR;
  if(n<1)
    return ERROR_SIZE;

  for(k = 0; k < n/2; k++)
  {
    tmp = x[k];
    x[k] = x[n-1-k];
    x[n-1-k] = tmp;
  }
  return RES_OK;
  
}



/******************************************************************************
\ingroup SPEC_MATH_COMMON_GROUP
\fn int flipip_cmplx(complex_t* x, int n)
\brief Flip complex vector `x` in place

Function flips complex vector `x` length `n` in the memory
 \n
For example complex vector `x`  length 6: \n
\verbatim
x = [0+0j, 1+1j, 2+2j, 3+3j, 4+4j, 5+5j]
\endverbatim
After flipping it will be as follow:
\verbatim
x = [5+5j, 4+4j, 3+3j, 2+2j, 1+1j, 0+0j]
\endverbatim

\param[in, out] x
Pointer to the complex vector `x`. \n
Vector size is `[n x 1]`. \n
Flipped vector will be on the same address. \n

\param[in] n
Length of the vector `x`. \n \n

\return
`RES_OK` if function returns successfully. \n
Else \ref ERROR_CODE_GROUP "error code".

Example:
\code{.cpp}
complex_t y[5] = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}, {4.0, 4.0}};
for(i = 0; i < 5; i++)
  printf("%6.1f%+.1fj  ", RE(y[i]), IM(y[i]));
flipip_cmplx(y, 5);
printf("\n");
for(i = 0; i < 5; i++)
  printf("%6.1f%+.1fj  ", RE(y[i]), IM(y[i]));
\endcode 
 \n
Program result:
\verbatim
   0.0+0.0j     1.0+1.0j     2.0+2.0j     3.0+3.0j     4.0+4.0j
   4.0+4.0j     3.0+3.0j     2.0+2.0j     1.0+1.0j     0.0+0.0j
\endverbatim

\author Sergey Bakhurin www.dsplib.org
*******************************************************************************/
int DSPL_API flipip_cmplx(complex_t* x, int n)
{
  int k;
  complex_t tmp;
  if(!x)
    return ERROR_PTR;
  if(n<1)
    return ERROR_SIZE;

  for(k = 0; k < n/2; k++)
  {
    RE(tmp) = RE(x[k]);
    RE(x[k]) = RE(x[n-1-k]);
    RE(x[n-1-k]) = RE(tmp);

    IM(tmp) = IM(x[k]);
    IM(x[k]) = IM(x[n-1-k]);
    IM(x[n-1-k]) = IM(tmp);
  }
  return RES_OK;
}






/*******************************************************************************
Linspace array filling
*******************************************************************************/
int DSPL_API linspace(double x0, double x1, int n, int type, double* x)
{
  double dx;
  int k;

  if(n < 2)
    return ERROR_SIZE;
  if(!x)
  return ERROR_PTR;

  switch (type)
  {
    case DSPL_SYMMETRIC:
      dx = (x1 - x0)/(double)(n-1);
      x[0] = x0;
      for(k = 1; k < n; k++)
        x[k] = x[k-1] + dx;
      break;
    case DSPL_PERIODIC:
      dx = (x1 - x0)/(double)n;
      x[0] = x0;
      for(k = 1; k < n; k++)
        x[k] = x[k-1] + dx;
      break;
    default:
      return ERROR_SYM_TYPE;
  }
  return RES_OK;
}





/*******************************************************************************
Logspace array filling
*******************************************************************************/
int DSPL_API logspace(double x0, double x1, int n, int type, double* x)
{
  double mx, a, b;
  int k;

  if(n < 2)
    return ERROR_SIZE;
  if(!x)
    return ERROR_PTR;

  a = pow(10.0, x0);
  b = pow(10.0, x1);

  switch (type)
  {
    case DSPL_SYMMETRIC:
      mx = pow(b/a, 1.0/(double)(n-1));
      x[0] = a;
      for(k = 1; k < n; k++)
        x[k] = x[k-1] * mx;
      break;
    case DSPL_PERIODIC:
      mx = pow(b/a, 1.0/(double)n);
      x[0] = a;
      for(k = 1; k < n; k++)
        x[k] = x[k-1] * mx;
      break;
    default:
      return ERROR_SYM_TYPE;
  }
  return RES_OK;
}


/*******************************************************************************
Ones double array
*******************************************************************************/
int DSPL_API ones(double* x, int n)
{
  int i;
  if(!x)
    return ERROR_PTR;
  if(n<1)
    return ERROR_SIZE;
  for(i = 0; i < n; i++)
    x[i] = 1.0;
 return RES_OK;
}


/******************************************************************************
\ingroup SPEC_MATH_COMMON_GROUP
\fn int verif(double* x,  double* y, size_t n, double eps, double* err)
\brief Real arrays verification

Function calculates a maximum relative error between two real arrays `x` 
and `y` (both length equals `n`):

\f[
e = \max \left( \frac{|x(k) - y(k)| }{ |x(k)|} \right), \quad if \quad |x(k)| > 0,
\f]
or 
\f[
e = \max(|x(k) - y(k)| ), ~\qquad if \quad~|x(k)| = 0,
\f]
Return `DSPL_VERIF_SUCCESS` if maximum relative error \f$ e\f$ less than `eps`. 
Else returns `DSPL_VERIF_FAILED`. \n

This function can be used for algorithms verification if vector `x` is user 
algorithm result and vector `y` -- reference vector.

\param[in] x
Pointer to the first vector `x`. \n
Vector size is `[n x 1]`. \n \n

\param[in] y
Pointer to the second vector `y`. \n
Vector size is `[n x 1]`. \n \n

\param[in] n
Size of vectors `x` and `y`. \n \n

\param[in] eps
Relative error threshold. \n
If error less than `eps`, then function returns 
`DSPL_VERIF_SUCCESS`, else `DSPL_VERIF_FAILED`.  \n \n

\param[in, out] err
Pointer to the variable which keep 
maximum relative error. \n
Pointer can be `NULL`, maximum error will not be returned 
in this case. \n \n

\return
`DSPL_VERIF_SUCCESS` if maximum relative error less than `eps`. \n
Otherwise `DSPL_VERIF_FAILED`.

\author Sergey Bakhurin www.dsplib.org
*******************************************************************************/
int DSPL_API verif(double* x,  double* y, size_t n, double eps, double* err)
{
  double d, maxd; 
  size_t k; 
  int res;
  if(!x || !y)
    return ERROR_PTR;
  if(n < 1)
    return ERROR_SIZE;
  if(eps <= 0.0 )
    return ERROR_NEGATIVE;
    
  maxd = -100.0;
  
  for(k = 0; k < n; k++)
  {
    d = fabs(x[k] - y[k]);
    if(fabs(x[k]) > 0.0)
    {
      d = d / fabs(x[k]);
      if(d > maxd)
        maxd = d;
    }
  }
  if(err) 
    *err = maxd;
    
  if(maxd > eps)
    res = DSPL_VERIF_FAILED;
  else
    res = DSPL_VERIF_SUCCESS;
 
  return res;
}



/******************************************************************************
\ingroup SPEC_MATH_COMMON_GROUP
\fn int verif_cmplx(complex_t* x,  complex_t* y, size_t n, 
                    double eps, double* err)
\brief
Complex arrays verification

Function calculates a maximum relative error between two complex arrays `x` 
and `y` (both length equals `n`):

\f[
e = \max \left( \frac{|x(k) - y(k)| }{ |x(k)|} \right), \quad if \quad |x(k)| > 0,
\f]
or 
\f[
e = \max(|x(k) - y(k)| ), ~\qquad if \quad~|x(k)| = 0,
\f]
Return `DSPL_VERIF_SUCCESS` if maximum relative error \f$ e\f$ less than `eps`. 
Else returns `DSPL_VERIF_FAILED`. \n

This function can be used for algorithms verification if vector `x` is user 
algorithm result and vector `y` -- reference vector.

\param[in] x
Pointer to the first vector `x`. \n
Vector size is `[n x 1]`. \n \n

\param[in] y
Pointer to the second vector `y`. \n
Vector size is `[n x 1]`. \n \n

\param[in] n
Size of vectors `x` and `y`. \n \n

\param[in] eps
Relative error threshold. \n
If error less than `eps`, then function returns 
`DSPL_VERIF_SUCCESS`, else `DSPL_VERIF_FAILED`.  \n \n

\param[in, out] err
Pointer to the variable which keep 
maximum relative error. \n
Pointer can be `NULL`, maximum error will not be returned 
in this case. \n \n

\return
`DSPL_VERIF_SUCCESS` if maximum relative error less than `eps`. \n
Otherwise `DSPL_VERIF_FAILED`.

\author
Sergey Bakhurin
www.dsplib.org
*******************************************************************************/
int DSPL_API verif_cmplx(complex_t* x,  complex_t* y, size_t n, 
         double eps, double* err)
{
  
  complex_t d;
  double mx, md, maxd;
  size_t k;
  int res;
  if(!x || !y)
    return ERROR_PTR;
  if(n < 1)
    return ERROR_SIZE;
  if(eps <= 0.0 )
    return ERROR_NEGATIVE;
    
  maxd = -100.0;
  
  for(k = 0; k < n; k++)
  {
    RE(d) = RE(x[k]) - RE(y[k]);
    IM(d) = IM(x[k]) - IM(y[k]);
    md = ABS(d);
    mx = ABS(x[k]);
    if(mx > 0.0)
    {
      md = md / mx;
      if(md > maxd)
        maxd = md;
    }
  }
  if(err)
    *err = maxd;
    
  if(maxd > eps)
    res = DSPL_VERIF_FAILED;
  else
    res = DSPL_VERIF_SUCCESS;
 
  return res;
}
