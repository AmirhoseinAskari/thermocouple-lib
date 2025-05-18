# thermocouple-lib

Temperature-voltage conversion utilities for thermocouples in C/C++

## 🔧 Features

- Supports thermocouple types: `K`, `J`, `T`, `E`, `N`, `R`, `S`, `B`  
- Convert voltage (mV) ↔ temperature (°C)  
- Polynomial approximation for high accuracy  
- Lightweight, portable C code  
- **Developed with consideration of MISRA-C guidelines** for safety-critical and embedded systems  
- **Temperature and voltage ranges compliant with IEC 60584 standard** for thermocouples

## 🧪 API Reference

### `double TC_CalculateTemperature(ThermocoupleType type, double voltage)`

Converts thermocouple voltage (in mV) to temperature (in °C).  
Returns the temperature, or `TC_CONVERSION_FAILED` if the voltage is out of range.

### `double TC_CalculateVoltage(ThermocoupleType type, double temperature)`

Converts temperature (in °C) to thermocouple voltage (in mV).  
Returns the voltage, or `TC_CONVERSION_FAILED` if the temperature is out of range.

## 💡 Example

An example showing how to use the library is in example/main.c.

## 📌 Thermocouple Types

| Type Name | Enum Value    |
|-----------|---------------|
| Type R    | `TC_TYPE_R`   |
| Type S    | `TC_TYPE_S`   |
| Type B    | `TC_TYPE_B`   |
| Type J    | `TC_TYPE_J`   |
| Type T    | `TC_TYPE_T`   |
| Type E    | `TC_TYPE_E`   |
| Type K    | `TC_TYPE_K`   |
| Type N    | `TC_TYPE_N`   |

## 📜 License

This project is licensed under the [MIT License](./LICENSE).

## 👤 Author

**Amirhossein Askari**  
📧 theamiraskarii@gmail.com  
🔗 [GitHub Profile](https://github.com/AmirhoseinAskari)
