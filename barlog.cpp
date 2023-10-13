#include <fstream>
#include <cstring>
#define NMAX 104
#define MMAX 104
#define LGMAX 21
#define ND 4
using namespace std;
ifstream fin("barlog.in");
ofstream fout("barlog.out");
struct camera
{
	int i, j;
};
bool subsir(char a[], char b[]);
int main()
{
	int crt, n, m, i, j, lin, col, k, inc, sf, nrc, gasit, nrmin;
	char a[NMAX][MMAX][LGMAX], cuv[LGMAX];
	int dl[] = {-1, 0, 1, 0};
	int dc[] = {0, 1, 0, -1};
	int b[NMAX][MMAX];
	camera cd[NMAX*MMAX], c, v;
	fin >> crt >> n >> m;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			fin >> a[i][j];
		}
	}
	fin >> lin >> col >> cuv;
	fin.close();
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			b[i][j] = -1;
		}
	}
	for (j = 0; j <= m+1; j++)
	{
		b[0][j] = b[n+1][j] = -2;
	}
	for (i = 0; i <= n+1; i++)
	{
		b[i][0] = b[i][m+1] = -2;
	}
	inc = sf = 0;
	cd[sf].i = lin, cd[sf].j = col;
	b[lin][col] = 1;
	while (inc <= sf)
	{
		c = cd[inc++];
		if (subsir(a[c.i][c.j], cuv))
		{
			for (k = 0; k < ND; k++)
			{
				v.i = c.i+dl[k];
				v.j = c.j+dc[k];
				if (b[v.i][v.j] == -1)
				{
					b[v.i][v.j] = 1+b[c.i][c.j];
					cd[++sf] = v;
				}
			}
		}
	}
	nrc = gasit = 0;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			if (b[i][j] > 0)
			{
				nrc++;
				if (i == 1 || i == n || j == 1 || j == m)
				{
					if (!gasit)
					{
						nrmin = b[i][j];
						gasit = 1;
					}
					else if (b[i][j] < nrmin)
					{
						nrmin = b[i][j];
					}
				}
			}
		}
	}
	if (crt == 1)
	{
		fout << nrc;
	}
	else
	{
		fout << nrmin;
	}
	fout.close();
	return 0;
}
bool subsir(char a[], char b[])
{
	int i, n;
	char *p;
	n = strlen(a);
	for (p = b, i = 0; i < n; i++, p++)
	{
		p = strchr(p, a[i]);
		if (!p)
		{
			return 0;
		}
	}
	return 1;
}
// scor 60
