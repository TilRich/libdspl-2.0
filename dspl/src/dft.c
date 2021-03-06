/*
* Copyright (c) 2015-2019 Sergey Bakhurin
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


#include <stdlib.h>
#include <math.h>
#include "dspl.h"



/******************************************************************************
\ingroup DFT_GROUP
\fn int dft(double* x, int n, complex_t* y)
\brief `n`-points discrete Fourier transform of the real vector `x`.

Function calculates \f$ n \f$-points  discrete Fourier transform of 
the real vector \f$ x(m) \f$, \f$ m = 0 \ldots n-1 \f$. \n
\f[
  Y(k) = \sum_{m = 0}^{n-1} x(m)   
  \exp \left( -j   \frac{2\pi}{n}    m    k \right),
\f]
here \f$ k = 0 \ldots n-1 \f$.

\param[in]  x    Pointer to the real input  
                 signal vector \f$x(m)\f$, 
                 \f$ m = 0 \ldots n-1 \f$.  \n
                 Vector size is `[n x 1]`.  \n \n

\param[in]  n    DFT size \f$n\f$ (size of input and output vectors). \n \n

\param[out]  y   Pointer to the complex DFT output vector \f$Y(k)\f$, 
                 \f$ k = 0 \ldots n-1 \f$.  \n
                 Vector size is `[n x 1]`.  \n
                 Memory must be allocated. \n \n


\return `RES_OK` if DFT is calculated successfully.  \n
Else \ref ERROR_CODE_GROUP "code error".

Example:

\include dft_test.c

Program output:

\verbatim
      y[ 0] =   120.000    0.000
      y[ 1] =    -8.000   40.219
      y[ 2] =    -8.000   19.314
      y[ 3] =    -8.000   11.973
      y[ 4] =    -8.000    8.000
      y[ 5] =    -8.000    5.345
      y[ 6] =    -8.000    3.314
      y[ 7] =    -8.000    1.591
      y[ 8] =    -8.000    0.000
      y[ 9] =    -8.000   -1.591
      y[10] =    -8.000   -3.314
      y[11] =    -8.000   -5.345
      y[12] =    -8.000   -8.000
      y[13] =    -8.000  -11.973
      y[14] =    -8.000  -19.314
      y[15] =    -8.000  -40.219
\endverbatim

\note
This function uses naive DFT algorithm and requires \f$ n^2 \f$ 
operations. You can use fast Fourier transform algorithms 
for DFT performance improvement.

\author Sergey Bakhurin www.dsplib.org 
*******************************************************************************/
int DSPL_API dft(double* x, int n, complex_t* y)
{
  int k;
  int m;
  double divn;
  double phi;


  if(!x || !y)
    return ERROR_PTR;

  if(n<1)
    return ERROR_SIZE;

  divn = 1.0 / (double)n;

  for(k = 0; k < n; k++)
  {
    RE(y[k]) = IM(y[k]) = 0.0;
    for(m = 0; m < n; m++)
    {
      phi  = -M_2PI * divn * (double)k * (double)m;
      RE(y[k]) += x[m] * cos(phi);
      IM(y[k]) += x[m] * sin(phi);
    }
  }
  return RES_OK;
}



/******************************************************************************
\ingroup DFT_GROUP
\fn int dft_cmplx(complex_t* x, int n, complex_t* y)
\brief `n`-points discrete Fourier transform of the complex vector `x`.

Function calculates \f$ n \f$-points  discrete Fourier transform of 
the complex vector \f$ x(m) \f$, \f$ m = 0 \ldots n-1 \f$. \n
\f[
  Y(k) = \sum_{m = 0}^{n-1} x(m)   
  \exp \left( -j   \frac{2\pi}{n}    m    k \right),
\f]
here \f$ k = 0 \ldots n-1 \f$.

\param[in]  x    Pointer to the complex input  
                 signal vector \f$x(m)\f$, 
                 \f$ m = 0 \ldots n-1 \f$.  \n
                 Vector size is `[n x 1]`.  \n \n

\param[in]  n    DFT size \f$n\f$ (size of input and output vectors). \n \n

\param[out]  y   Pointer to the complex DFT output vector \f$Y(k)\f$, 
                 \f$ k = 0 \ldots n-1 \f$.  \n
                 Vector size is `[n x 1]`.  \n
                 Memory must be allocated. \n \n


\return `RES_OK` if DFT is calculated successfully.  \n
Else \ref ERROR_CODE_GROUP "code error".

Example:

\include dft_cmplx_test.c

Program output:

\verbatim
      y[ 0] =   120.000    0.000
      y[ 1] =    -8.000   40.219
      y[ 2] =    -8.000   19.314
      y[ 3] =    -8.000   11.973
      y[ 4] =    -8.000    8.000
      y[ 5] =    -8.000    5.345
      y[ 6] =    -8.000    3.314
      y[ 7] =    -8.000    1.591
      y[ 8] =    -8.000    0.000
      y[ 9] =    -8.000   -1.591
      y[10] =    -8.000   -3.314
      y[11] =    -8.000   -5.345
      y[12] =    -8.000   -8.000
      y[13] =    -8.000  -11.973
      y[14] =    -8.000  -19.314
      y[15] =    -8.000  -40.219
\endverbatim

\note
This function uses naive DFT algorithm and requires \f$ n^2 \f$ 
operations. You can use fast Fourier transform algorithms 
for DFT performance improvement.

\author Sergey Bakhurin www.dsplib.org 
*******************************************************************************/
int DSPL_API dft_cmplx(complex_t* x, int n, complex_t* y)
{
  int k;
  int m;
  double divn;
  double phi;
  complex_t e;

  if(!x || !y)
    return ERROR_PTR;

  if(n<1)
    return ERROR_SIZE;

  divn = 1.0 / (double)n;

  for(k = 0; k < n; k++)
  {
    RE(y[k]) = IM(y[k]) = 0.0;
    for(m = 0; m < n; m++)
    {
      phi  = -M_2PI * divn * (double)k * (double)m;
      RE(e) = cos(phi);
      IM(e) = sin(phi);
      RE(y[k]) += CMRE(x[m], e);
      IM(y[k]) += CMIM(x[m], e);
    }
  }
  return RES_OK;
}





/******************************************************************************
\ingroup DFT_GROUP
\fn int idft_cmplx(complex_t* x, int n, complex_t* y)
\brief `n`-points inverse discrete Fourier transform of the complex vector `x`.

Function calculates \f$ n \f$-points inverse discrete Fourier transform of 
the complex vector \f$ x(m) \f$, \f$ m = 0 \ldots n-1 \f$. \n
\f[
  y(k) = \sum_{m = 0}^{n-1} x(m)   
  \exp \left( j   \frac{2\pi}{n}    m    k \right),
\f]
here \f$ k = 0 \ldots n-1 \f$.

\param[in]  x    Pointer to the complex input  
                 vector \f$x(m)\f$, 
                 \f$ m = 0 \ldots n-1 \f$.  \n
                 Vector size is `[n x 1]`.  \n \n

\param[in]  n    IDFT size \f$n\f$ (size of input and output vectors). \n \n

\param[out]  y   Pointer to the complex IDFT output vector \f$y(k)\f$, 
                 \f$ k = 0 \ldots n-1 \f$.  \n
                 Vector size is `[n x 1]`.  \n
                 Memory must be allocated. \n \n


\return `RES_OK` if IDFT is calculated successfully.  \n
Else \ref ERROR_CODE_GROUP "code error".

Example:

\include idft_cmplx_test.c

Program output:

\verbatim
x[ 0] =     0.000   +0.000j,    z[ 0] =     0.000   -0.000
x[ 1] =     1.000   +0.000j,    z[ 1] =     1.000   -0.000
x[ 2] =     2.000   +0.000j,    z[ 2] =     2.000   -0.000
x[ 3] =     3.000   +0.000j,    z[ 3] =     3.000   -0.000
x[ 4] =     4.000   +0.000j,    z[ 4] =     4.000   -0.000
x[ 5] =     5.000   +0.000j,    z[ 5] =     5.000   -0.000
x[ 6] =     6.000   +0.000j,    z[ 6] =     6.000   -0.000
x[ 7] =     7.000   +0.000j,    z[ 7] =     7.000   -0.000
x[ 8] =     8.000   +0.000j,    z[ 8] =     8.000   -0.000
x[ 9] =     9.000   +0.000j,    z[ 9] =     9.000   -0.000
x[10] =    10.000   +0.000j,    z[10] =    10.000   -0.000
x[11] =    11.000   +0.000j,    z[11] =    11.000   +0.000
x[12] =    12.000   +0.000j,    z[12] =    12.000   +0.000
x[13] =    13.000   +0.000j,    z[13] =    13.000   +0.000
x[14] =    14.000   +0.000j,    z[14] =    14.000   +0.000
x[15] =    15.000   +0.000j,    z[15] =    15.000   -0.000
\endverbatim

\note
This function uses naive IDFT algorithm and requires \f$ n^2 \f$ 
operations. You can use fast Fourier transform algorithms 
for DFT performance improvement.

\author Sergey Bakhurin www.dsplib.org 
*******************************************************************************/
int DSPL_API idft_cmplx(complex_t* x, int n, complex_t* y)
{
  int k;
  int m;
  double divn;
  double phi;
  complex_t e;

  if(!x || !y)
    return ERROR_PTR;

  if(n<1)
    return ERROR_SIZE;

  divn = 1.0 / (double)n;

  for(k = 0; k < n; k++)
  {
    RE(y[k]) = IM(y[k]) = 0.0;
    for(m = 0; m < n; m++)
    {
      phi  =  M_2PI * divn * (double)k * (double)m;
      RE(e) = cos(phi);
      IM(e) = sin(phi);
      RE(y[k]) += CMRE(x[m], e);
      IM(y[k]) += CMIM(x[m], e);
    }
    RE(y[k]) /= (double)n;
    IM(y[k]) /= (double)n;
  }
  return RES_OK;
}

