﻿using System;

namespace Catrobat.IDE.Core.ExtensionMethods
{
    public static class RandomExtensions
    {
        public static bool NextBool(this Random random)
        {
            return random.NextDouble() < 0.5;
        }
    
        public static double NextSignedDouble(this Random random)
        {
            return -random.NextDouble();
        }
    }
}