#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

static const char *pcTextForTask1 = "Task 1 is running\r\n";
static const char *pcTextForTask2 = "Task 2 is running\r\n";
static const char *pcTextForTask3 = "periodic Task is running\r\n";

static void vTask1(void *pvParameters){
  char *pcTaskName;
  TickType_t xLastWakeTime;

  pcTaskName = ( char * ) pvParameters;
  xLastWakeTime = xTaskGetTickCount();
  for (;;){
    Serial.print(pcTaskName);
    vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( 500 ) );
  }
}

static void vTask2( void *pvParameters ){
  char *pcTaskName;
  pcTaskName = ( char * ) pvParameters;

  for( ;; ){
    Serial.print( pcTaskName );
    vTaskDelay(1);
  }
}

static void vPeriodicTask( void *pvParameters ){
  pinMode(LED_BUILTIN,OUTPUT);
  TickType_t xLastWakeTime;
  const TickType_t xDelay100ms = pdMS_TO_TICKS( 1000 );
  xLastWakeTime = xTaskGetTickCount();
  /* As per most tasks, this task is implemented in an infinite loop. */
  for( ;; )
  {
  /* Print out the name of this task. */
  Serial.print( "Periodic task is running\r\n" );
  digitalWrite(LED_BUILTIN, HIGH);
  vTaskDelayUntil( &xLastWakeTime, xDelay100ms );
  digitalWrite(LED_BUILTIN, LOW);
  }
}

void setup() {
  Serial.begin(9600);
    xTaskCreate(vTask1,"vTask1",128,(void*)pcTextForTask1,1,NULL);
    xTaskCreate(vTask2,"vTask2",128,(void*)pcTextForTask2,1, NULL);
    xTaskCreate(vPeriodicTask,"pTask",256,(void*)pcTextForTask3,2,NULL);
    vTaskStartScheduler();
}

void loop() {
  
}