| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- |

# Component: XGZF4000

<a href="https://components.espressif.com/components/hayschan/xgzf4000">
<img src="https://components.espressif.com/components/hayschan/xgzf4000/badge.svg" alt="hayschan/xgzf4000 Version: 0.9.3" />
</a>

I2C driver and definition for XGZF4000 air flow sensor.

See [XGZF4000 online datasheet](https://cfsensor.com/wp-content/uploads/2022/11/XGZF4000-Air-Flow-Sensor-V2.2.pdf).

In addition to the online version of the XGZF4000 Air Flow Sensor datasheet, an [archived copy](/docs/XGZF4000-Air-Flow-Sensor-V2.2.pdf) is also available within the repository. This archived version can be found at the location `./docs/XGZF4000-Air-Flow-Sensor-V2.2.pdf`. This ensures that users have access to the datasheet even in offline scenarios or if the online version becomes unavailable.

## Using the driver

### Operation modes
New data from XGZF4000 can be obtained in Polling modes.

> Note: The user is responsible for initialization and configuration of I2C bus.

After calling `xgzf4000_new_sensor()`, the user is responsible for periodically reading the air flow data from XGZF4000.

## Simulator

To simulate this project, install [Wokwi for VS Code](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode). Open the project (at `./simulation`) directory in Visual Studio Code, press **F1** and select "Wokwi: Start Simulator".

> Please note that Wokwi for VS Code is a commercial product and requires a license after a free trial period.

You may also use the online Wokwi simulator with [this sample project](https://wokwi.com/projects/385249858064235521).
