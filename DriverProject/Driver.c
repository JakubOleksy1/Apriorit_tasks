#include <ntddk.h>

void UnloadDriver(PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);
    KdPrint(("HelloWorldDriver: Unload\n"));
}

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);
    DriverObject->DriverUnload = UnloadDriver;
    KdPrint(("HelloWorldDriver: DriverEntry\n"));
    return STATUS_SUCCESS;
}