### Introduction
`atv-control` is an Arduino Project that started from finding a solution to manage the operating time of atv vehicles in an amusement park. When a guest buys a ticket, that guest will have 20 minutes to use an atv. At the 19th minute, the system will warn that the usage time is about to run out so that the guest can drive to the appropriate return point. Each atv has a safety module that detects unsafe elements to stop the vehicle appropriately.

The project uses object-oriented design:
1. Manual dependency injecting for dependencies management.
2. A global message queue `MessageQueue` to decouple the system.
3. A (non-blocking) software job scheduler `JobScheduler`.
4. `DevicePowerController`, `SafetyModule`, `SessionManager`, `AlertSystem` are logical models for real world entities.