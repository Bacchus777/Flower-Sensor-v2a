#ifndef ZCL_APP_H
#define ZCL_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * INCLUDES
 */
#include "version.h"
#include "zcl.h"


/*********************************************************************
 * CONSTANTS
 */

#define FIRST_ENDPOINT                  1
  
// Application Events
#define APP_REPORT_EVT                  0x0001
#define APP_READ_SENSORS_EVT            0x0002
#define APP_SAVE_ATTRS_EVT              0x0004

#define NW_APP_CONFIG                   0x0402


#define AIR_COMPENSATION_FORMULA(ADC)   ((0.179 * (double)ADC + 3926.0))
#define WATER_COMPENSATION_FORMULA(ADC) ((0.156 * (double)ADC + 1500.0))



#define APP_REPORT_DELAY ((uint32) 1800000) //30 minutes


/*********************************************************************
 * MACROS
 */

#define R           ACCESS_CONTROL_READ
#define RR          (R | ACCESS_REPORTABLE)
#define RW          (R | ACCESS_CONTROL_WRITE | ACCESS_CONTROL_AUTH_WRITE)
#define RWR         (RW | ACCESS_REPORTABLE)

#define BASIC           ZCL_CLUSTER_ID_GEN_BASIC
#define POWER_CFG       ZCL_CLUSTER_ID_GEN_POWER_CFG
#define TEMP            ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT
#define HUMIDITY        ZCL_CLUSTER_ID_MS_RELATIVE_HUMIDITY
#define PRESSURE        ZCL_CLUSTER_ID_MS_PRESSURE_MEASUREMENT
#define ILLUMINANCE     ZCL_CLUSTER_ID_MS_ILLUMINANCE_MEASUREMENT
#define GEN_ON_OFF      ZCL_CLUSTER_ID_GEN_ON_OFF

#define ZCL_UINT8       ZCL_DATATYPE_UINT8
#define ZCL_UINT16      ZCL_DATATYPE_UINT16
#define ZCL_UINT32      ZCL_DATATYPE_UINT32
#define ZCL_INT16       ZCL_DATATYPE_INT16
#define ZCL_INT8        ZCL_DATATYPE_INT8
#define ZCL_BOOLEAN     ZCL_DATATYPE_BOOLEAN


#define ATTRID_MS_RELATIVE_HUMIDITY_MEASURED_VALUE_RAW_ADC              0x0200
#define ATTRID_MS_RELATIVE_HUMIDITY_MEASURED_VALUE_BATTERY_RAW_ADC      0x0201
#define ATTRID_MS_THRESHOLD                                             0x0202



/*********************************************************************
 * TYPEDEFS
 */

typedef struct {
    uint16    Threshold;
} application_config_t;


/*********************************************************************
 * VARIABLES
 */

extern SimpleDescriptionFormat_t zclApp_FirstEP;

extern void zclApp_ResetAttributesToDefaultValues(void);

extern uint8 zclApp_BatteryVoltage;
extern uint8 zclApp_BatteryPercentageRemainig;
extern uint16 zclApp_BatteryVoltageRawAdc;
extern int16 zclApp_Temperature_Sensor_MeasuredValue;
extern int16 zclApp_PressureSensor_MeasuredValue;
extern int16 zclApp_PressureSensor_ScaledValue;
extern int8 zclApp_PressureSensor_Scale;
extern uint16 zclApp_HumiditySensor_MeasuredValue;
extern int16 zclApp_DS18B20_MeasuredValue;
extern uint16 zclApp_SoilHumiditySensor_MeasuredValue;
extern uint16 zclApp_SoilHumiditySensor_MeasuredValueRawAdc;
extern uint16 zclApp_IlluminanceSensor_MeasuredValue;
extern uint16 zclApp_IlluminanceSensor_MeasuredValueRawAdc;
extern bool zclApp_SoilHumiditySensor_Output;

// attribute list
extern CONST zclAttrRec_t zclApp_AttrsFirstEP[];
extern CONST uint8 zclApp_AttrsFirstEPCount;


extern const uint8 zclApp_ManufacturerName[];
extern const uint8 zclApp_ModelId[];
extern const uint8 zclApp_PowerSource;

extern application_config_t zclApp_Config;

// APP_TODO: Declare application specific attributes here

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Initialization for the task
 */
extern void zclApp_Init(byte task_id);

extern void zclApp_ResetAttributesToDefaultValues(void);

/*
 *  Event Process for the task
 */
extern UINT16 zclApp_event_loop(byte task_id, UINT16 events);

void user_delay_ms(uint32_t period);

#ifdef __cplusplus
}
#endif

#endif /* ZCL_APP_H */
