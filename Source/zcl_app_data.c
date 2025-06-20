#include "AF.h"
#include "OSAL.h"
#include "ZComDef.h"
#include "ZDConfig.h"

#include "zcl.h"
#include "zcl_general.h"
#include "zcl_ms.h"
#include "zcl_ha.h"

#include "zcl_app.h"

#include "battery.h"
#include "version.h"
/*********************************************************************
 * CONSTANTS
 */

#define APP_DEVICE_VERSION 2
#define APP_FLAGS 0

#define APP_HWVERSION 1
#define APP_ZCLVERSION 1

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

// Global attributes
const uint16 zclApp_clusterRevision_all = 0x0001;

int16   zclApp_Temperature_Sensor_MeasuredValue = 0;
int16   zclApp_PressureSensor_MeasuredValue = 0;
int16   zclApp_PressureSensor_ScaledValue = 0;
int8    zclApp_PressureSensor_Scale = -1;

uint16  zclApp_SoilHumiditySensor_MeasuredValue = 0;
uint16  zclApp_SoilHumiditySensor_MeasuredValueRawAdc = 0;
bool    zclApp_SoilHumiditySensor_Output = 0;

int16   zclApp_DS18B20_MeasuredValue = 0;

uint16  zclApp_IlluminanceSensor_MeasuredValue = 0;
uint16  zclApp_IlluminanceSensor_MeasuredValueRawAdc = 0;

// Basic Cluster
const uint8 zclApp_HWRevision = APP_HWVERSION;
const uint8 zclApp_ZCLVersion = APP_ZCLVERSION;
const uint8 zclApp_ApplicationVersion = 3;
const uint8 zclApp_StackVersion = 4;

const uint8 zclApp_ManufacturerName[] = {7, 'B', 'a', 'c', 'c', 'h', 'u', 's'};
const uint8 zclApp_ModelId[] = {17, 'F', 'l', 'o', 'w', 'e', 'r', '_', 's', 'e', 'n', 's', 'o', 'r', '_', 'v', '2', 'a'};
const uint8 zclApp_PowerSource = POWER_SOURCE_BATTERY;


/*********************************************************************
 * ATTRIBUTE DEFINITIONS - Uses REAL cluster IDs
 */


// msTemperatureMeasurement int16
// msRelativeHumidity:  uint16
// msPressureMeasurement   int16
// msIlluminanceMeasurement uint16
// #define ZCL_CLUSTER_ID_GEN_BASIC                             0x0000
// #define ZCL_CLUSTER_ID_GEN_POWER_CFG                         0x0001
// #define ZCL_CLUSTER_ID_MS_ILLUMINANCE_MEASUREMENT            0x0400
// #define ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT            0x0402
// #define ZCL_CLUSTER_ID_MS_PRESSURE_MEASUREMENT               0x0403

CONST zclAttrRec_t zclApp_AttrsFirstEP[] = {
    {BASIC, {ATTRID_BASIC_ZCL_VERSION, ZCL_UINT8, R, (void *)&zclApp_ZCLVersion}},
    {BASIC, {ATTRID_BASIC_APPL_VERSION, ZCL_UINT8, R, (void *)&zclApp_ApplicationVersion}},
    {BASIC, {ATTRID_BASIC_STACK_VERSION, ZCL_UINT8, R, (void *)&zclApp_StackVersion}},
    {BASIC, {ATTRID_BASIC_HW_VERSION, ZCL_UINT8, R, (void *)&zclApp_HWRevision}},
    {BASIC, {ATTRID_BASIC_MANUFACTURER_NAME, ZCL_DATATYPE_CHAR_STR, R, (void *)zclApp_ManufacturerName}},
    {BASIC, {ATTRID_BASIC_MODEL_ID, ZCL_DATATYPE_CHAR_STR, R, (void *)zclApp_ModelId}},
    {BASIC, {ATTRID_BASIC_DATE_CODE, ZCL_DATATYPE_CHAR_STR, R, (void *)zclApp_DateCode}},
    {BASIC, {ATTRID_BASIC_POWER_SOURCE, ZCL_DATATYPE_ENUM8, R, (void *)&zclApp_PowerSource}},
    {BASIC, {ATTRID_BASIC_SW_BUILD_ID, ZCL_DATATYPE_CHAR_STR, R, (void *)zclApp_DateCode}},
    {BASIC, {ATTRID_CLUSTER_REVISION, ZCL_DATATYPE_UINT16, R, (void *)&zclApp_clusterRevision_all}},

    {POWER_CFG, {ATTRID_POWER_CFG_BATTERY_VOLTAGE, ZCL_UINT8, RR, (void *)&zclBattery_Voltage}},
    {POWER_CFG, {ATTRID_POWER_CFG_BATTERY_PERCENTAGE_REMAINING, ZCL_UINT8, RR, (void *)&zclBattery_PercentageRemainig}},
    {POWER_CFG, {ATTRID_POWER_CFG_BATTERY_VOLTAGE_RAW_ADC, ZCL_UINT16, RR, (void *)&zclBattery_RawAdc}},


    {ILLUMINANCE, {ATTRID_MS_ILLUMINANCE_MEASURED_VALUE, ZCL_UINT16, R, (void *)&zclApp_IlluminanceSensor_MeasuredValue}},
    {TEMP, {ATTRID_MS_TEMPERATURE_MEASURED_VALUE, ZCL_INT16, R, (void *)&zclApp_DS18B20_MeasuredValue}},

    {HUMIDITY, {ATTRID_MS_RELATIVE_HUMIDITY_MEASURED_VALUE, ZCL_UINT16, R, (void *)&zclApp_SoilHumiditySensor_MeasuredValue}},
    {HUMIDITY, {ATTRID_MS_RELATIVE_HUMIDITY_MEASURED_VALUE_RAW_ADC, ZCL_UINT16, R, (void *)&zclApp_SoilHumiditySensor_MeasuredValueRawAdc}},
    {HUMIDITY, {ATTRID_MS_RELATIVE_HUMIDITY_MEASURED_VALUE_BATTERY_RAW_ADC, ZCL_UINT16, R, (void *)&zclBattery_RawAdc}},
};


uint8 CONST zclApp_AttrsFirstEPCount = (sizeof(zclApp_AttrsFirstEP) / sizeof(zclApp_AttrsFirstEP[0]));


const cId_t zclApp_InClusterListFirstEP[] = {ZCL_CLUSTER_ID_GEN_BASIC, POWER_CFG, ILLUMINANCE, TEMP, HUMIDITY};

#define APP_MAX_INCLUSTERS_FIRST_EP (sizeof(zclApp_InClusterListFirstEP) / sizeof(zclApp_InClusterListFirstEP[0]))


SimpleDescriptionFormat_t zclApp_FirstEP = {
    1,                                                  //  int Endpoint;
    ZCL_HA_PROFILE_ID,                                  //  uint16 AppProfId[2];
    ZCL_HA_DEVICEID_SIMPLE_SENSOR,                      //  uint16 AppDeviceId[2];
    APP_DEVICE_VERSION,                                 //  int   AppDevVer:4;
    APP_FLAGS,                                          //  int   AppFlags:4;
    APP_MAX_INCLUSTERS_FIRST_EP,                        //  byte  AppNumInClusters;
    (cId_t *)zclApp_InClusterListFirstEP,               //  byte *pAppInClusterList;
    0,                                                  //  byte  AppNumOutClusters;
    (cId_t *)NULL                                       //  byte *pAppOutClusterList;  
};