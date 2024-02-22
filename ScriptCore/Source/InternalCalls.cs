using System.Runtime.CompilerServices;

namespace Cobalt
{
    internal class InternalCalls
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public static void EngineLog_Trace(string message);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public static void EngineLog_Info(string message);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public static void EngineLog_Warn(string message);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public static void EngineLog_Error(string message);
    }
}
