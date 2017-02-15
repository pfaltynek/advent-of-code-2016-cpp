using System;
using System.Collections.Generic;

namespace ConsoleApplication {
	public class Program {
		public class Step {
			public uint x, y, step;

			public Step(uint x_init, uint y_init, uint step_init) {
				x = x_init;
				y = y_init;
				step = step_init;
			}
		}
		public static bool IsEvenParity(UInt32 v) {
			v ^= v >> 1;
			v ^= v >> 2;
			v = (v & 0x11111111U) * 0x11111111U;
			return ((v >> 28) & 1) != 1;
		}

		public static bool IsSpace(uint x, uint y, uint number) {
			return IsEvenParity((x * x) + (3 * x) + (2 * x * y) + y + (y * y) + number);
		}

		private static Dictionary<uint, bool> map = new Dictionary<uint, bool>();
		private static List<Step> queue = new List<Step>();

		private static uint GetCoord(uint x, uint y) {
			return (1000 * x) + y;
		}

		private static uint FindIt(uint startx, uint starty, uint targetx, uint targety, uint number) {
			uint result = 0, coord;
			uint target = GetCoord(targetx, targety);
			queue.Add(new Step(startx, starty, 0));
			Step step;
			bool space;

			while (queue.Count > 0) {
				step = queue[0];
				queue.RemoveAt(0);

				coord = GetCoord(step.x, step.y);

				if (coord == target) {
					result = step.step;
					break;
				}

				if (map.ContainsKey(coord)) {
					continue;
				}
				space = IsSpace(step.x, step.y, number);
				map.Add(coord, space);
				if (space) {
					if (step.x > 0) {
						queue.Add(new Step(step.x - 1, step.y, step.step + 1));
					}
					if (step.y > 0) {
						queue.Add(new Step(step.x, step.y - 1, step.step + 1));
					}
					queue.Add(new Step(step.x + 1, step.y, step.step + 1));
					queue.Add(new Step(step.x, step.y + 1, step.step + 1));
				}
			}
			return result;
		}

		public static void Main(string[] args) {
			//uint test = FindIt(1, 1, 7, 4, 10);
			uint result1 = FindIt(1, 1, 31, 39, 1364);
		}

		/*
				public static bool IsEvenParity2(UInt32 x)
				{

					x ^= x >> 16;
					x ^= x >> 8;
					x ^= x >> 4;
					x ^= x >> 2;
					x ^= x >> 1;
					return ((~x) & 1) == 1;
				}
		*/
	}
}
