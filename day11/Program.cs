// rewrite of JAVA code from https://github.com/exoji2e/aoc16-language-challenge/blob/master/11-java/A.java
using System;
using System.Collections.Generic;
using System.Text;

namespace AoC_day11 {
	class Program {
		private class FuncCall {
			public int[] n;
			public int k;
			public int e;
			public FuncCall(int[] n, int k, int e) {
				this.n = new int[n.Length];
				for (int i = 0; i < n.Length; i++) {
					this.n[i] = n[i];
				}
				this.k = k;
				this.e = e;
			}
		}

		private class Pair : IComparable<Pair> {
			public int x, y;
			public Pair(int x, int y) {
				this.x = x; this.y = y;
			}

			public int CompareTo(Pair p) {
				if (x != p.x) {
					return x - p.x;
				}
				return y - p.y;
			}
		}

		private static int DoIt(int[] n, out long time) {
			int result = -1;
			System.Diagnostics.Stopwatch stopwatch = System.Diagnostics.Stopwatch.StartNew();
			HashSet<string> map = new HashSet<string>();
			StringBuilder sb = new StringBuilder();
			String finalstate;
			List<FuncCall> bfs = new List<FuncCall>();
			String s;

			for (int i = 0; i <= n.Length; i++) {
				sb.Append('3');
			}
			finalstate = sb.ToString();
			bfs.Add(new FuncCall(n, 0, 0));
			while (bfs.Count > 0) {
				FuncCall f = bfs[0];
				bfs.RemoveAt(0);
				if (f.e < 0 || f.e > 3) continue; //elevator outside building
				sortx(f.n);
				if (!ok(f.n)) continue; //microship gets fried
				s = getStr(f.n, f.e);
				if (map.Contains(s)) continue; //state we've already been to.
				map.Add(s);
				if (s.Equals(finalstate)) { //found final state!
					result = f.k;
					break;
				}


				for (int i = 0; i < f.n.Length; i++) {
					if (f.n[i] != f.e) continue;
					f.n[i]--;
					bfs.Add(new FuncCall(f.n, f.k + 1, f.e - 1)); //move n[i]
					bool mvnxt = i % 2 == 0 && f.n[i + 1] == f.e;
					if (mvnxt) {
						f.n[i + 1]--;
						bfs.Add(new FuncCall(f.n, f.k + 1, f.e - 1)); //move n[i]
						f.n[i + 1]++;
					}
					f.n[i] += 2;
					bfs.Add(new FuncCall(f.n, f.k + 1, f.e + 1)); //move n[i]
					if (mvnxt) {
						f.n[i + 1]++;
						bfs.Add(new FuncCall(f.n, f.k + 1, f.e + 1)); //move n[i]
						f.n[i + 1]--;
					}
					f.n[i]--;

					for (int j = i + 2; j < f.n.Length; j += 2) {
						if (f.n[j] != f.e) continue;
						f.n[i]--; f.n[j]--;
						bfs.Add(new FuncCall(f.n, f.k + 1, f.e - 1)); //move n[i]&n[j]
						f.n[i] += 2; f.n[j] += 2;
						bfs.Add(new FuncCall(f.n, f.k + 1, f.e + 1)); //move n[i]&n[j]
						f.n[i]--; f.n[j]--;
					}
				}
			}

			stopwatch.Stop();
			time = stopwatch.ElapsedMilliseconds;
			return result;
		}

		public static void sortx(int[] n) {
			Pair[] pairs = new Pair[n.Length / 2];
			for (int i = 0; i < pairs.Length; i++) {
				pairs[i] = new Pair(n[2 * i], n[2 * i + 1]);
			}
			Array.Sort(pairs);
			for (int i = 0; i < pairs.Length; i++) {
				n[2 * i] = pairs[i].x;
				n[2 * i + 1] = pairs[i].y;
			}
		}

		public static bool ok(int[] n) {
			for (int i = 0; i < n.Length; i += 2) //microships
				if (n[i] != n[i + 1])
					for (int j = 1; j < n.Length; j += 2) //generator
						if (n[j] == n[i])  //microship getting fried. 
							return false;

			return true;
		}

		public static String getStr(int[] n, int e) {
			StringBuilder sb = new StringBuilder();
			sb.Append(e);
			for (int i = 0; i < n.Length; i++) {
				sb.Append(n[i]);
			}
			return sb.ToString();
		}

		static void Main(string[] args) {
			int x = 0, x1 = 0, x2 = 0;
			long time = 0, t1 = 0, t2 = 0;

			Console.WriteLine("=== Advent of Code 2016 - day 11 ====");
			x = DoIt(new int[] { 0, 1, 0, 2 }, out time);
			Console.WriteLine("--- test ---");
			Console.WriteLine("Result is: {0} ({1}ms)", x, time);
			x1 = DoIt(new int[] { 0, 0, 2, 1, 2, 1, 2, 1, 2, 1 }, out t1);
			Console.WriteLine("--- part 1 ---");
			Console.WriteLine("Result is: {0} ({1}ms)", x1, t1);
			x2 = DoIt(new int[] { 0, 0, 2, 1, 2, 1, 2, 1, 2, 1, 0, 0, 0, 0 }, out t2);
			Console.WriteLine("--- part 2 ---");
			Console.WriteLine("Result is: {0} ({1}ms)", x2, t2);
		}
	}
}
