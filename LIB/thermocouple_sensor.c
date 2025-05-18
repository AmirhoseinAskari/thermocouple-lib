/**
 * @file    thermocouple_sensor.c
 * @author  Amirhossein Askari
 * @version v1.0.0
 * @date    2025-03-24
 * @email   theamiraskarii@gmail.com
 * @see     https://github.com/AmirhoseinAskari
 * @brief   Source file for thermocouple temperature-voltage conversions.
 * 
 * @details
 * Implements functions for converting temperature to voltage and vice versa
 * for thermocouple types R, S, B, J, K, E, N, and T. The conversions use polynomial
 * approximations to ensure accurate results.
 * 
 * @note
 * Ensure the correct thermocouple type is provided as input to the conversion functions.
 *  
 * @warning
 * Always verify that temperature and voltage inputs are within supported ranges
 * to ensure accurate and safe conversions
 */


/* ------------------------------------- Includes -------------------------------------- */

#include "thermocouple_sensor.h"    ///< Header file for thermocouple functions



/* ------------------------------------- Variables ------------------------------------- */

/* -------------------------------- Thermocouple Type R -------------------------------- */
static const double TC_Coeff_R_mVToTemp_Range1[] =
{
    0.0000000E+00,  1.8891380E+02, -9.3835290E+01, 1.3068619E+02,
    -2.2703580E+02, 3.5145659E+02, -3.8953900E+02, 2.8239471E+02,
    -1.2607281E+02, 3.1353611E+01, -3.3187769E+00
};
static const double TC_Coeff_R_mVToTemp_Range2[] =
{
    1.334584505E+01,  1.472644573E+02, -1.844024844E+01, 4.031129726E+00,
    -6.249428360E-01, 6.468412046E-02, -4.458750426E-03, 1.994710149E-04,
    -5.313401790E-06, 6.481976217E-08, 0.000000000E+00
};
static const double TC_Coeff_R_mVToTemp_Range3[] =
{
    -8.199599416E+01, 1.553962042E+02, -8.342197663E+00, 4.279433549E-01,
    -1.191577910E-02, 1.492290091E-04, 0.000000000E+00,  0.000000000E+00,
    0.000000000E+00,  0.000000000E+00, 0.000000000E+00
};
static const double TC_Coeff_R_mVToTemp_Range4[] =
{
    3.406177836E+04, -7.023729171E+03, 5.582903813E+02, -1.952394635E+01,
    2.560740231E-01, 0.000000000E+00,  0.000000000E+00, 0.000000000E+00,
    0.000000000E+00, 0.000000000E+00,  0.000000000E+00
};
static const RangePoly TC_R_mVToTemp[] =
{
{ -0.228, 1.923,  { TC_Coeff_R_mVToTemp_Range1, sizeof(TC_Coeff_R_mVToTemp_Range1) / sizeof(double) } },
{ 1.923,  11.361, { TC_Coeff_R_mVToTemp_Range2, sizeof(TC_Coeff_R_mVToTemp_Range2) / sizeof(double) } },
{ 11.361, 19.739, { TC_Coeff_R_mVToTemp_Range3, sizeof(TC_Coeff_R_mVToTemp_Range3) / sizeof(double) } },
{ 19.739, 21.105, { TC_Coeff_R_mVToTemp_Range4, sizeof(TC_Coeff_R_mVToTemp_Range4) / sizeof(double) } }
};
static const size_t TC_R_mVToTemp_len = sizeof(TC_R_mVToTemp) / sizeof(TC_R_mVToTemp[0U]);

static const double TC_Coeff_R_TempToMV_Range1[] =
{
    0.000000000000E+00, 0.528961729765E-02,  0.139166589782E-04, -0.238855693017E-07,
    0.356916001063E-10, -0.462347666298E-13, 0.500777441034E-16, -0.373105886191E-19,
    0.157716482367E-22, -0.281038625251E-26
};
static const double TC_Coeff_R_TempToMV_Range2[] =
{
    0.295157925316E+01,  -0.252061251332E-02, 0.159564501865E-04,
    -0.764085947576E-08, 0.205305291024E-11,  -0.293359668173E-15
};
static const double TC_Coeff_R_TempToMV_Range3[] =
{
    0.152232118209E+03,  -0.268819888545E+00, 0.171280280471E-03,
    -0.345895706453E-07, -0.934633971046E-14
};
static const RangePoly TC_R_TempToMV[] =
{
{ -50.5,   1064.18, { TC_Coeff_R_TempToMV_Range1, sizeof(TC_Coeff_R_TempToMV_Range1) / sizeof(double) } },
{ 1064.18, 1664.5,  { TC_Coeff_R_TempToMV_Range2, sizeof(TC_Coeff_R_TempToMV_Range2) / sizeof(double) } },
{ 1664.5,  1768.5,  { TC_Coeff_R_TempToMV_Range3, sizeof(TC_Coeff_R_TempToMV_Range3) / sizeof(double) } }
};
static const size_t TC_R_TempToMV_len = sizeof(TC_R_TempToMV) / sizeof(TC_R_TempToMV[0U]);


/* -------------------------------- Thermocouple Type S -------------------------------- */
static const double TC_Coeff_S_mVToTemp_Range1[] =
{
    0.00000000E+00,  1.84949460E+02, -8.00504062E+01, 1.02237430E+02,
    -1.52248592E+02, 1.88821343E+02, -1.59085941E+02, 8.23027880E+01,
    -2.34181944E+01, 2.79786260E+00
};
static const double TC_Coeff_S_mVToTemp_Range2[] =
{
    1.291507177E+01,  1.466298863E+02, -1.534713402E+01, 3.145945973E+00,
    -4.163257839E-01, 3.187963771E-02, -1.291637500E-03, 2.183475087E-05,
    -1.447379511E-07, 8.211272125E-09
};
static const double TC_Coeff_S_mVToTemp_Range3[] =
{
    -8.087801117E+01, 1.621573104E+02, -8.536869453E+00, 4.719686976E-01,
    -1.441693666E-02, 2.081618890E-04, 0.000000000E+00,  0.000000000E+00,
    0.000000000E+00,  0.000000000E+00
};
static const double TC_Coeff_S_mVToTemp_Range4[] =
{
    5.333875126E+04, -1.235892298E+04, 1.092657613E+03, -4.265693686E+01,
    6.247205420E-01, 0.000000000E+00,  0.000000000E+00, 0.000000000E+00,
    0.000000000E+00, 0.000000000E+00
};
static const RangePoly TC_S_mVToTemp[] =
{
{ -0.237, 1.874,  { TC_Coeff_S_mVToTemp_Range1, sizeof(TC_Coeff_S_mVToTemp_Range1) / sizeof(double) } },
{ 1.874,  10.332, { TC_Coeff_S_mVToTemp_Range2, sizeof(TC_Coeff_S_mVToTemp_Range2) / sizeof(double) } },
{ 10.332, 17.536, { TC_Coeff_S_mVToTemp_Range3, sizeof(TC_Coeff_S_mVToTemp_Range3) / sizeof(double) } },
{ 17.536, 18.697, { TC_Coeff_S_mVToTemp_Range4, sizeof(TC_Coeff_S_mVToTemp_Range4) / sizeof(double) } }
};
static const size_t TC_S_mVToTemp_len = sizeof(TC_S_mVToTemp) / sizeof(TC_S_mVToTemp[0U]);

static const double TC_Coeff_S_TempToMV_Range1[] =
{
    0.000000000000E+00,  0.540313308631E-02,  0.125934289740E-04,
    -0.232477968689E-07, 0.322028823036E-10, -0.331465196389E-13,
    0.255744251786E-16,  -0.125068871393E-19, 0.271443176145E-23
};
static const double TC_Coeff_S_TempToMV_Range2[] =
{
    0.132900444085E+01,  0.334509311344E-02, 0.654805192818E-05,
    -0.164856259209E-08, 0.129989605174E-13
};
static const double TC_Coeff_S_TempToMV_Range3[] =
{
    0.146628232636E+03, -0.258430516752E+00, 0.163693574641E-03,
    -0.330439046987E-07, -0.943223690612E-14
};
static const RangePoly TC_S_TempToMV[] =
{
{ -50.5,   1064.18, { TC_Coeff_S_TempToMV_Range1, sizeof(TC_Coeff_S_TempToMV_Range1) / sizeof(double) } },
{ 1064.18, 1664.5,  { TC_Coeff_S_TempToMV_Range2, sizeof(TC_Coeff_S_TempToMV_Range2) / sizeof(double) } },
{ 1664.5,  1768.5,  { TC_Coeff_S_TempToMV_Range3, sizeof(TC_Coeff_S_TempToMV_Range3) / sizeof(double) } }
};
static const size_t TC_S_TempToMV_len = sizeof(TC_S_TempToMV) / sizeof(TC_S_TempToMV[0U]);
  

/* -------------------------------- Thermocouple Type B -------------------------------- */
static const double TC_Coeff_B_mVToTemp_Range1[] =
{
    9.8423321E+01, 6.9971500E+02,  -8.4765304E+02,
    1.0052644E+03, -8.3345952E+02, 4.5508542E+02,
    -1.5523037E+02, 2.9886750E+01, -2.4742860E+00
};
static const double TC_Coeff_B_mVToTemp_Range2[] =
{
    2.1315071E+02, 2.8510504E+02,  -5.2742887E+01,
    9.9160804E+00, -1.2965303E+00, 1.1195870E-01,
    -6.0625199E-03, 1.8661696E-04, -2.4878585E-06
};
static const RangePoly TC_B_mVToTemp[] =
{
{ 0.292, 2.431,  { TC_Coeff_B_mVToTemp_Range1, sizeof(TC_Coeff_B_mVToTemp_Range1) / sizeof(double) } },
{ 2.431, 13.825, { TC_Coeff_B_mVToTemp_Range2, sizeof(TC_Coeff_B_mVToTemp_Range2) / sizeof(double) } }
};
static const size_t TC_B_mVToTemp_len = sizeof(TC_B_mVToTemp) / sizeof(TC_B_mVToTemp[0U]);

static const double TC_Coeff_B_TempToMV_Range1[] =
{
    0.000000000000E+00, -0.246508183460E-03, 0.590404211710E-05, -0.132579316360E-08,
    0.156682919010E-11, -0.169445292400E-14, 0.629903470940E-18
};
static const double TC_Coeff_B_TempToMV_Range2[] =
{
    -0.389381686210E+01, 0.285717474700E-01, -0.848851047850E-04,
    0.157852801640E-06, -0.168353448640E-09,  0.111097940130E-12,
    -0.445154310330E-16, 0.989756408210E-20, -0.937913302890E-24
};
static const RangePoly TC_B_TempToMV[] =
{
{ -0.5,   630.615, { TC_Coeff_B_TempToMV_Range1, sizeof(TC_Coeff_B_TempToMV_Range1) / sizeof(double) } },
{ 630.615, 1820.5, { TC_Coeff_B_TempToMV_Range2, sizeof(TC_Coeff_B_TempToMV_Range2) / sizeof(double) } }
};
static const size_t TC_B_TempToMV_len = sizeof(TC_B_TempToMV) / sizeof(TC_B_TempToMV[0U]);
 

/* -------------------------------- Thermocouple Type J -------------------------------- */
static const double TC_Coeff_J_mVToTemp_Range1[] =
{
    0.0000000E+00,  1.9528268E+01,  -1.2286185E+00,
    -1.0752178E+00, -5.9086933E-01, -1.7256713E-01,
    -2.8131513E-02, -2.3963370E-03, -8.3823321E-05
};
static const double TC_Coeff_J_mVToTemp_Range2[] =
{
    0.000000E+00, 1.978425E+01, -2.001204E-01,
    1.036969E-02, -2.549687E-04, 3.585153E-06,
    -5.344285E-08, 5.099890E-10, 0.000000E+00
};
static const double TC_Coeff_J_mVToTemp_Range3[] =
{
    -3.11358187E+03, 3.00543684E+02,  -9.94773230E+00,
    1.70276630E-01,  -1.43033468E-03, 4.73886084E-06,
    0.00000000E+00,  0.00000000E+00,  0.00000000E+00
};
static const RangePoly TC_J_mVToTemp[] =
{
{ -8.1, 0.0,     { TC_Coeff_J_mVToTemp_Range1, sizeof(TC_Coeff_J_mVToTemp_Range1) / sizeof(double) } },
{ 0.0,   42.914, { TC_Coeff_J_mVToTemp_Range2, sizeof(TC_Coeff_J_mVToTemp_Range2) / sizeof(double) } },
{ 42.914, 69.58, { TC_Coeff_J_mVToTemp_Range3, sizeof(TC_Coeff_J_mVToTemp_Range3) / sizeof(double) } }
};
static const size_t TC_J_mVToTemp_len = sizeof(TC_J_mVToTemp) / sizeof(TC_J_mVToTemp[0U]);

static const double TC_Coeff_J_TempToMV_Range1[] =
{
    0.000000000000E+00,  0.503811878150E-01,  0.304758369300E-04,
    -0.856810657200E-07, 0.132281952950E-09, -0.170529583370E-12,
    0.209480906970E-15, -0.125383953360E-18,  0.156317256970E-22
};
static const double TC_Coeff_J_TempToMV_Range2[] =
{
    0.296456256810E+03, -0.149761277860E+01, 0.317871039240E-02,
    -0.318476867010E-05, 0.157208190040E-08, -0.306913690560E-12
};
static const RangePoly TC_J_TempToMV[] =
{
{ -210.5, 760.0, { TC_Coeff_J_TempToMV_Range1, sizeof(TC_Coeff_J_TempToMV_Range1) / sizeof(double) } },
{ 760.0, 1200.5, { TC_Coeff_J_TempToMV_Range2, sizeof(TC_Coeff_J_TempToMV_Range2) / sizeof(double) } }
};
static const size_t TC_J_TempToMV_len = sizeof(TC_J_TempToMV) / sizeof(TC_J_TempToMV[0U]);
  

/* -------------------------------- Thermocouple Type T -------------------------------- */
static const double TC_Coeff_T_mVToTemp_Range1[] =
{
    0.0000000E+00, 2.5949192E+01, -2.1316967E-01, 7.9018692E-01,
    4.2527777E-01, 1.3304473E-01, 2.0241446E-02,  1.2668171E-03
};
static const double TC_Coeff_T_mVToTemp_Range2[] =
{
    0.000000E+00,  2.592800E+01, -7.602961E-01, 4.637791E-02,
    -2.165394E-03, 6.048144E-05, -7.293422E-07, 0.000000E+00
};
static const RangePoly TC_T_mVToTemp[] =
{
{ -5.61, 0.0,   { TC_Coeff_T_mVToTemp_Range1, sizeof(TC_Coeff_T_mVToTemp_Range1) / sizeof(double) } },
{ 0.0,   20.88, { TC_Coeff_T_mVToTemp_Range2, sizeof(TC_Coeff_T_mVToTemp_Range2) / sizeof(double) } }
};
static const size_t TC_T_mVToTemp_len = sizeof(TC_T_mVToTemp) / sizeof(TC_T_mVToTemp[0U]);

static const double TC_Coeff_T_TempToMV_Range1[] =
{
    0.000000000000E+00, 0.387481063640E-01, 0.441944343470E-04,
    0.118443231050E-06, 0.200329735540E-07, 0.901380195590E-09,
    0.226511565930E-10, 0.360711542050E-12, 0.384939398830E-14,
    0.282135219250E-16, 0.142515947790E-18, 0.487686622860E-21,
    0.107955392700E-23, 0.139450270620E-26, 0.797951539270E-30
};
static const double TC_Coeff_T_TempToMV_Range2[] =
{
    0.000000000000E+00, 0.387481063640E-01, 0.332922278800E-04,
    0.206182434040E-06, -0.218822568460E-08, 0.109968809280E-10,
    -0.308157587720E-13, 0.454791352900E-16, -0.275129016730E-19
};
static const RangePoly TC_T_TempToMV[] =
{
{ -270.5, 0.0, { TC_Coeff_T_TempToMV_Range1, sizeof(TC_Coeff_T_TempToMV_Range1) / sizeof(double) } },
{ 0.0,  400.5, { TC_Coeff_T_TempToMV_Range2, sizeof(TC_Coeff_T_TempToMV_Range2) / sizeof(double) } }
};
static const size_t TC_T_TempToMV_len = sizeof(TC_T_TempToMV) / sizeof(TC_T_TempToMV[0U]);
   

/* -------------------------------- Thermocouple Type E -------------------------------- */
static const double TC_Coeff_E_mVToTemp_Range1[] =
{
    0.0000000E+00,  1.6977288E+01,  -4.3514970E-01, -1.5859697E-01,
    -9.2502871E-02, -2.6084314E-02, -4.1360199E-03, -3.4034030E-04,
    -1.1564890E-05, 0.0000000E+00
};
static const double TC_Coeff_E_mVToTemp_Range2[] =
{
    0.0000000E+00,  1.7057035E+01, -2.3301759E-01, 6.5435585E-03,
    -7.3562749E-05, -1.7896001E-06, 8.4036165E-08, -1.3735879E-09,
    1.0629823E-11,  -3.2447087E-14
};
static const RangePoly TC_E_mVToTemp[] =
{
{ -8.84, 0.0, { TC_Coeff_E_mVToTemp_Range1, sizeof(TC_Coeff_E_mVToTemp_Range1) / sizeof(double) } },
{ 0.0, 76.38, { TC_Coeff_E_mVToTemp_Range2, sizeof(TC_Coeff_E_mVToTemp_Range2) / sizeof(double) } }
};
static const size_t TC_E_mVToTemp_len = sizeof(TC_E_mVToTemp) / sizeof(TC_E_mVToTemp[0U]);

static const double TC_Coeff_E_TempToMV_Range1[] =
{
    0.000000000000E+00,   0.586655087080E-01,  0.454109771240E-04, -0.779980486860E-06,
    -0.258001608430E-07, -0.594525830570E-09, -0.932140586670E-11, -0.102876055340E-12,
    -0.803701236210E-15, -0.439794973910E-17, -0.164147763550E-19, -0.396736195160E-22,
    -0.558273287210E-25, -0.346578420130E-28
};
static const double TC_Coeff_E_TempToMV_Range2[] =
{
    0.000000000000E+00,  0.586655087100E-01, 0.450322755820E-04,  0.289084072120E-07,
    -0.330568966520E-09, 0.650244032700E-12, -0.191974955040E-15, -0.125366004970E-17,
    0.214892175690E-20, -0.143880417820E-23, 0.359608994810E-27
}; 
static const RangePoly TC_E_TempToMV[] =
{
{ -270.5, 0.0,  { TC_Coeff_E_TempToMV_Range1, sizeof(TC_Coeff_E_TempToMV_Range1) / sizeof(double) } },
{ 0.0,  1000.5, { TC_Coeff_E_TempToMV_Range2, sizeof(TC_Coeff_E_TempToMV_Range2) / sizeof(double) } }
};
static const size_t TC_E_TempToMV_len = sizeof(TC_E_TempToMV) / sizeof(TC_E_TempToMV[0U]);


/* -------------------------------- Thermocouple Type K -------------------------------- */
static const double TC_Coeff_K_mVToTemp_Range1[] =
{
    0.0000000E+00,  2.5173462E+01,  -1.1662878E+00, -1.0833638E+00,
    -8.9773540E-01, -3.7342377E-01, -8.6632643E-02, -1.0450598E-02,
    -5.1920577E-04, 0.0000000E+00
};
static const double TC_Coeff_K_mVToTemp_Range2[] =
{
    0.000000E+00, 2.508355E+01,  7.860106E-02, -2.503131E-01,
    8.315270E-02, -1.228034E-02, 9.804036E-04, -4.413030E-05,
    1.057734E-06, -1.052755E-08
};
static const double TC_Coeff_K_mVToTemp_Range3[] =
{
    -1.318058E+02, 4.830222E+01, -1.646031E+00, 5.464731E-02,
    -9.650715E-04, 8.802193E-06, -3.110810E-08, 0.000000E+00,
    0.000000E+00,  0.000000E+00
};
static const RangePoly TC_K_mVToTemp[] =
{
{ -5.895, 0.0,    { TC_Coeff_K_mVToTemp_Range1, sizeof(TC_Coeff_K_mVToTemp_Range1) / sizeof(double) } },
{ 0.0,    20.644, { TC_Coeff_K_mVToTemp_Range2, sizeof(TC_Coeff_K_mVToTemp_Range2) / sizeof(double) } },
{ 20.644, 52.425, { TC_Coeff_K_mVToTemp_Range3, sizeof(TC_Coeff_K_mVToTemp_Range3) / sizeof(double) } }
};
static const size_t TC_K_mVToTemp_len = sizeof(TC_K_mVToTemp) / sizeof(TC_K_mVToTemp[0U]);

static const double TC_Coeff_K_TempToMV_A0 =  0.118597600000E+00;
static const double TC_Coeff_K_TempToMV_A1 = -0.118343200000E-03;
static const double TC_Coeff_K_TempToMV_A2 =  0.126968600000E+03;
static const double TC_Coeff_K_TempToMV_Range1[] =
{
    0.000000000000E+00,   0.394501280250E-01,  0.236223735980E-04, -0.328589067840E-06,
    -0.499048287770E-08, -0.675090591730E-10, -0.574103274280E-12, -0.310888728940E-14,
    -0.104516093650E-16, -0.198892668780E-19, -0.163226974860E-22
};
static const double TC_Coeff_K_TempToMV_Range2[] =
{
    -0.176004136860E-01, 0.389212049750E-01, 0.185587700320E-04, -0.994575928740E-07,
    0.318409457190E-09, -0.560728448890E-12, 0.560750590590E-15, -0.320207200030E-18,
    0.971511471520E-22, -0.121047212750E-25
};
  

/* -------------------------------- Thermocouple Type N -------------------------------- */
static const double TC_Coeff_N_mVToTemp_Range1[] =
{
    0.0000000E+00, 3.8436847E+01, 1.1010485E+00, 5.2229312E+00,
    7.2060525E+00, 5.8488586E+00, 2.7754916E+00, 7.7075166E-01,
    1.1582665E-01, 7.3138868E-03
};
static const double TC_Coeff_N_mVToTemp_Range2[] =
{
    0.00000E+00,  3.86896E+01,  -1.08267E+00, 4.70205E-02,
    -2.12169E-06, -1.17272E-04, 5.39280E-06, -7.98156E-08,
    0.00000E+00,  0.00000E+00
};
static const double TC_Coeff_N_mVToTemp_Range3[] =
{
    1.972485E+01,  3.300943E+01, -3.915159E-01, 9.855391E-03,
    -1.274371E-04, 7.767022E-07, 0.000000E+00,  0.000000E+00,
    0.000000E+00,  0.000000E+00
};
static const RangePoly TC_N_mVToTemp[] =
{
{ -4,    0.0,    { TC_Coeff_N_mVToTemp_Range1, sizeof(TC_Coeff_N_mVToTemp_Range1) / sizeof(double) } },
{ 0.0,   20.613, { TC_Coeff_N_mVToTemp_Range2, sizeof(TC_Coeff_N_mVToTemp_Range2) / sizeof(double) } },
{ 20.613, 47.52, { TC_Coeff_N_mVToTemp_Range3, sizeof(TC_Coeff_N_mVToTemp_Range3) / sizeof(double) } }
};
static const size_t TC_N_mVToTemp_len = sizeof(TC_N_mVToTemp) / sizeof(TC_N_mVToTemp[0U]);

static const double TC_Coeff_N_TempToMV_Range1[] =
{
    0.000000000000E+00,   0.261591059620E-01,  0.109574842280E-04,
    -0.938411115540E-07, -0.464120397590E-10, -0.263033577160E-11,
    -0.226534380030E-13, -0.760893007910E-16, -0.934196678350E-19
};
static const double TC_Coeff_N_TempToMV_Range2[] =
{
    0.000000000000E+00,  0.259293946010E-01,  0.157101418800E-04,
    0.438256272370E-07, -0.252611697940E-09,  0.643118193390E-12,
    -0.100634715190E-14, 0.997453389920E-18, -0.608632456070E-21,
    0.208492293390E-24, -0.306821961510E-28
};
static const RangePoly TC_N_TempToMV[] =
{
{ -270.5, 0.0,  { TC_Coeff_N_TempToMV_Range1, sizeof(TC_Coeff_N_TempToMV_Range1) / sizeof(double) } },
{ 0.0,  1300.5, { TC_Coeff_N_TempToMV_Range2, sizeof(TC_Coeff_N_TempToMV_Range2) / sizeof(double) } }
};
static const size_t TC_N_TempToMV_len = sizeof(TC_N_TempToMV) / sizeof(TC_N_TempToMV[0U]);



/* ------------------------------------- Functions ------------------------------------- */

/**
 * @brief Finds the appropriate polynomial coefficients for a given input value.
 *
 * @details
 * Searches through an array of range-to-polynomial mappings and returns a pointer
 * to the polynomial coefficients corresponding to the range containing the input value.
 *
 * @param[in] ranges Pointer to the array of range-to-polynomial mappings.
 * @param[in] len    Number of elements in the @p ranges array.
 * @param[in] value  Input value to locate within the defined ranges.
 *
 * @return Pointer to the matching polynomial coefficients if a range is found;
 *         otherwise, returns @c NULL if the input value is outside all ranges.
 *
 * @note    Performs a linear search; consider optimizing if @p len is large.
 * @warning Ensure that the @p ranges array is correctly defined and covers all required input values.
 */
static const PolyCoeff *FindPolyCoeff(const RangePoly *ranges, size_t len, double value)
{
    const PolyCoeff *result = NULL;
    size_t i;

    for (i = 0U; i < len; ++i)
    {
        if ((value >= ranges[i].min) && (value <= ranges[i].max))
        {
            result = &ranges[i].poly;
            break;
        }
    }

    return result; /* NULL if no valid range found */
}

/**
 * @brief Evaluates a polynomial at a given input using Horner's method.
 * 
 * @details
 * Efficiently computes the value of a polynomial of arbitrary degree at the specified input,
 * leveraging Horner's method to improve computational efficiency and numerical stability.
 *
 * @param[in] pCoefficient Pointer to an array of polynomial coefficients.
 * @param[in] length        Number of coefficients in the polynomial (degree + 1).
 * @param[in] input         The input value at which to evaluate the polynomial.
 *
 * @return The polynomial value evaluated at the input.
 *
 * @warning Ensure that @p length is greater than zero and @p pCoefficient is not @c NULL.
 */
static double Polynomial_Evaluate(const double *pCoefficient, uint8_t length, double input)
{
    double result = 0;
    for (int8_t i = length - 1; i >= 0; --i)
    {
        result = (result * input) + pCoefficient[i];
    }
    return result;
}

/**
 * @brief  Calculates temperature from thermocouple voltage.
 *
 * @details
 * Converts a voltage reading (in millivolts) from a specified thermocouple type
 * into a temperature value (in degrees Celsius) using type-specific polynomial approximations.
 *
 * @param[in]  type     Thermocouple type (e.g., @c TC_TYPE_K, @c TC_TYPE_J) as defined in the @c ThermocoupleType enum.
 * @param[in]  voltage  Measured voltage from the thermocouple in millivolts (mV).
 * 
 * @return Calculated temperature in degrees Celsius.
 *         Returns @c TC_CONVERSION_FAILED if the voltage is out of range or if the thermocouple type is invalid.
 *
 * @note     The function uses polynomial approximations specific to each thermocouple type.
 * @warning  Ensure the @p type is valid and the input voltage is within the supported range.
 */
double TC_CalculateTemperature(ThermocoupleType type, double voltage)
{	
    double temperature      = TC_CONVERSION_FAILED;    
    const RangePoly *ranges = NULL;
    const PolyCoeff *poly   = NULL;
    size_t ranges_len       = 0U;
     
    switch (type)
    { 
        case TC_TYPE_R:
            ranges = TC_R_mVToTemp;
            ranges_len = TC_R_mVToTemp_len;
        break;
                
        case TC_TYPE_S:
            ranges = TC_S_mVToTemp;
            ranges_len = TC_S_mVToTemp_len;
        break;
        
        case TC_TYPE_B:    
            ranges = TC_B_mVToTemp;
            ranges_len = TC_B_mVToTemp_len;
        break;
        
        case TC_TYPE_J:     
            ranges = TC_J_mVToTemp;
            ranges_len = TC_J_mVToTemp_len;
        break;
        
        case TC_TYPE_T:    
            ranges = TC_T_mVToTemp;
            ranges_len = TC_T_mVToTemp_len;
        break;
        
        case TC_TYPE_E:
            ranges = TC_E_mVToTemp;
            ranges_len = TC_E_mVToTemp_len;
        break;
        
        case TC_TYPE_K:
            ranges = TC_K_mVToTemp;
            ranges_len = TC_K_mVToTemp_len;
        break;
        
        case TC_TYPE_N:
            ranges = TC_N_mVToTemp;
            ranges_len = TC_N_mVToTemp_len;
        break;
        
        default:
            temperature = TC_CONVERSION_FAILED;
    }
    
    if (ranges != NULL)
    {
        poly = FindPolyCoeff(ranges, ranges_len, voltage);
        if (poly != NULL)
        {
            temperature = Polynomial_Evaluate(poly->pCoefficients, poly->length, voltage);
        }
    }

    return temperature;
}

/**
 * @brief  Calculates thermocouple voltage from temperature.
 *
 * @details
 * Converts a temperature value (in degrees Celsius) for a specified thermocouple type
 * into the corresponding voltage (in millivolts) using type-specific polynomial approximations.
 *
 * @param[in]  type         Thermocouple type (e.g., @c TC_TYPE_K, @c TC_TYPE_J) as defined in the @c ThermocoupleType enum.
 * @param[in]  temperature  Temperature in degrees Celsius (°C).
 * 
 * @return Calculated voltage in millivolts (mV).  
 *         Returns @c TC_CONVERSION_FAILED if the temperature is out of range or the thermocouple type is invalid.
 *
 * @note     The function uses polynomial approximations specific to each thermocouple type.
 * @warning  Ensure the @p type is valid and the input temperature is within the supported range.
 */
double TC_CalculateVoltage(ThermocoupleType type, double temperature)
{
    double voltage          = TC_CONVERSION_FAILED;    
    const RangePoly *ranges = NULL;
    const PolyCoeff *poly   = NULL;
    const double *pCoeff    = NULL;
    double correction       = 0;
    size_t ranges_len       = 0U;
    size_t length           = 0U;
      
    switch (type)
    { 
        case TC_TYPE_R:
            ranges = TC_R_TempToMV;
            ranges_len = TC_R_TempToMV_len;
        break;

        case TC_TYPE_S:
            ranges = TC_S_TempToMV;
            ranges_len = TC_S_TempToMV_len;
        break;

        case TC_TYPE_B:
            ranges = TC_B_TempToMV;
            ranges_len = TC_B_TempToMV_len;
        break;

        case TC_TYPE_J:
            ranges = TC_J_TempToMV;
            ranges_len = TC_J_TempToMV_len;
        break;

        case TC_TYPE_T:
            ranges = TC_T_TempToMV;
            ranges_len = TC_T_TempToMV_len;
        break;

        case TC_TYPE_E:
            ranges = TC_E_TempToMV;
            ranges_len = TC_E_TempToMV_len;
        break;

        case TC_TYPE_K:                     
            if ( (temperature >= -270.5) && (temperature <= 0.0) )
            {
                pCoeff = TC_Coeff_K_TempToMV_Range1;
                length = sizeof(TC_Coeff_K_TempToMV_Range1) / sizeof(double);
            }
            else if ( (temperature > 0.0) && (temperature <= 1372.5) )
            {
                pCoeff = TC_Coeff_K_TempToMV_Range2;
                length = sizeof(TC_Coeff_K_TempToMV_Range2) / sizeof(double);
            }
            else
            {
                voltage = TC_CONVERSION_FAILED;
            }

            voltage = Polynomial_Evaluate(pCoeff, length, temperature);

            if (temperature > 0.0)
            {
                correction = TC_Coeff_K_TempToMV_A0 * exp(TC_Coeff_K_TempToMV_A1 * pow((temperature - TC_Coeff_K_TempToMV_A2), 2.0));
                voltage += correction;
            }
        break;

        case TC_TYPE_N:
            ranges = TC_N_TempToMV;
            ranges_len = TC_N_TempToMV_len;
        break;
        
        default:
            voltage = TC_CONVERSION_FAILED;
    }
       
    if (ranges != NULL)
    {
        poly = FindPolyCoeff(ranges, ranges_len, temperature);
        if (poly != NULL)
        {
            voltage = Polynomial_Evaluate(poly->pCoefficients, poly->length, temperature);
        }
    }
       
    return voltage;
}


/* thermocouple_sensor.c */
