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
camera cd[NMAX*MMAX], c, v;
int dl[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
int br[NMAX][MMAX], inc, sf, nrc, gasit, nrmin;
bool subsir(char a[], char b[]);
int main()
{
	int crt, n, m, i, j, lin, col, k;
	char a[NMAX][MMAX][LGMAX], cuv[LGMAX];
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
	for (j = 0; j <= m+1; j++)
	{
		br[0][j] = br[n+1][j] = -1;
	}
	for (i = 0; i <= n+1; i++)
	{
		br[i][0] = br[i][m+1] = -1;
	}
	cd[sf].i = lin, cd[sf].j = col;
	br[lin][col] = 1;
	while (inc <= sf)
	{
		c = cd[inc++];
		if (subsir(a[c.i][c.j], cuv))
		{
			for (k = 0; k < ND; k++)
			{
				v.i = c.i+dl[k];
				v.j = c.j+dc[k];
				if (br[v.i][v.j] == 0)
				{
					br[v.i][v.j] = 1+br[c.i][c.j];
					cd[++sf] = v;
				}
				else if (br[v.i][v.j] == -1 && !gasit)
				{
					nrmin = br[c.i][c.j];
					gasit = 1;
				}
			}
		}
	}
	if (crt == 2)
	{
		fout << nrmin;
	}
	else if (crt == 1)
	{
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= m; j++)
			{
				if (br[i][j] > 0)
				{
					nrc++;
				}
			}
		}
		fout << nrc;
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
// scor 100
