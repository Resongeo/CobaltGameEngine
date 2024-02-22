using System;

namespace Cobalt
{
    public struct Vector3
    {
        public float X, Y, Z;

        public Vector3(float scalar)
        {
            X = scalar;
            Y = scalar;
            Z = scalar;
        }

        public Vector3(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public static Vector3 Normalize(Vector3 v)
        {
            float length = (float)Math.Sqrt((v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z));
            if (length < 1f) return v;
            return new Vector3(v.X / length, v.Y / length, v.Z / length);
        }

        public static Vector3 operator *(Vector3 other, float scalar)
        {
            return new Vector3(other.X * scalar, other.Y * scalar, other.Z * scalar);
        }
    }
}
