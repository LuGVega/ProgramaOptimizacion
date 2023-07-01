/*Equipo 3:
Gómez Vega Guadalupe
Este programa aplica el metodo simplex y 
el metodo simplex con una variable artificial*/
/*Librerias a incluir*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

/*Funciones*/
void datos()
{
	printf("Gomez Vega Guadalupe\n");
}
void datos(int *var, int *res)
{
	int r;
	do
	{
		printf("Cuantas variables de decision tienes? ");
		scanf("%d", var);
		printf("El numero es correcto?\n1)...SI\n2)...NO\nDigite opcion: ");
		scanf("%d", &r);
		if(r<1 || r>2 )
				printf("No existe respuesta. Ingrese 1 o 2\n");
	}while(r==2 || (r<1 || r>2 ));
	do
	{
		printf("Cuantas restricciones tienes tienes? ");
		scanf("%d", res);
		printf("El numero es correcto?\n1)...SI\n2)...NO\nDigite opcion: ");
		scanf("%d", &r);
		if(r<1 || r>2 )
				printf("No existe respuesta. Ingrese 1 o 2\n");
	}while(r==2 || (r<1 || r>2 ));
}
void ingresoDatos(int res, int var,double matV[][var], double matR[][res],double ld[res],double z[var])
{
	int x, y, v, r;
	//llanar la matriz matR con ceros
	for(x=0; x<res;++x)
	{
		for(y=0; y<res;++y)
		{
			matR[x][y]=0;
		}
	}
	printf("Ingrese los valores de la funcion objetivo\n");
	do
	{
		for(x=0;x<var;++x)
		{
			printf("x%d= ", x+1);
			scanf("%lf", &z[x]);
		}
		printf("Son correctos los valores?\n1)...SI\n2)...NO\nDigite opcion: ");
		scanf("%d", &r);
		if(r<1 || r>2 )
				printf("No existe respuesta. Ingrese 1 o 2\n");
	}while(r==2 || (r<1 || r>2 ));
	system("cls");
	for(x=0; x<res;++x)
	{
		printf("Ingresa los valores de la restriccion %d\n", x+1);
		printf("Ingrese los valores de las variables de decision:\n");
		fflush(stdin);
		do
		{
			for(v=0; v<var;++v)
			{
				printf("x%d= ", v+1);
				scanf("%lf", &matV[x][v]);
			}
			printf("Son correctos los valores?\n1)...SI\n2)...NO\nDigite opcion: ");
			scanf("%d", &r);
			if(r<1 || r>2 )
				printf("No existe respuesta. Ingrese 1 o 2\n");
		}while(r==2 || (r<1 || r>2 ));
		system("cls");
		printf("Ingrese variable de holgura de la restriccion %d\n",x+1);
		do
		{
			for(y=x; y<x+1; ++y)
			{
				printf("s%d= ", x+1);
				scanf("%lf", &matR[y][y]);
			}
			printf("Es correcto el valor?\n1)...SI\n2)...NO\nDigite opcion: ");
			scanf("%d", &r);
			if(r<1 || r>2 )
				printf("No existe respuesta. Ingrese 1 o 2\n");
		}while(r==2 || (r<1 || r>2 ));
		system("cls");
		do
		{
			printf("Ingrese Lado Derecho de la restriccion %d\nLD: ",x+1);
			scanf("%lf", &ld[x]);
			printf("Es correcto el valor?\n1)...SI\n2)...NO\nDigite opcion: ");
			scanf("%d", &r);
			if(r<1 || r>2 )
				printf("No existe respuesta. Ingrese 1 o 2\n");
		}while(r==2 || (r<1 || r>2 ));
		system("cls");
	}
	
}
void unir(int res, int var, double matV[][var],double  matR[][res], double ld[res], double z[var], double matS[][var+res+1])
{
	int x, y;
	//llenar con ceros la matriz matS
	for(x=0; x<res+1;++x)
	{
		for(y=0; y<res+var+1;++y)
		{
			matS[x][y]=0;
		}
	}
	//pasa z al renglon 0 de matS
	for(x=0;x<var;++x)
	{
		matS[0][x]=z[x];
	}
	//pasa matV a matS
	for(x=1;x<res+1;++x)
	{
		for(y=0;y<var;++y)
		{
			matS[x][y]=matV[x-1][y];
		}
	}
	//pasa matR a matS
	for(x=1;x<res+1;++x)
	{
		for(y=var;y<var+res;++y)
		{
			matS[x][y]=matR[x-1][y-var];
		}
	}
	// pasa ld a la ultima columna de matS
	for(x=0; x<res;++x)
	{
		matS[x+1][var+res]=ld[x];
	}
}

void imprimeMat(int res, int var,double  matS[][var+res+1])
{
	int x, y;
	for(x=0; x<var; ++x)
	{
		printf("%15s%d", "x", x+1);
	}
	for(x=0; x<res; ++x)
	{
		printf("%15s%d", "s", x+1);
	}
	printf("%15s\n", "LD");
	for(x=0; x<res+1;++x)
	{
		for(y=0;y<res+var+1;++y)
		{
			printf("%16lf", matS[x][y]);
		}
		printf("\n");
	}
}
void imprimeSimplex(int res, int var, double matS[][var+res+1])
{
	int x, y;
	for(x=0; x<var; ++x)
	{
		printf("%15s%d","x", x+1);
	}
	for(x=0; x<res; ++x)
	{
		printf("%15s%d", "s", x+1);
	}
	printf("%15s\n", "LD");
	for(x=0; x<res+1;++x)
	{
		for(y=0;y<res+var+1;++y)
		{
			printf("%16lf", matS[x][y]);
		}
		printf("\n");
	}
	printf("");
}
void imprimeSimplexArtificial(int res, int var,double matS[][var+res+2])
{
	int x, y;
	for(x=0; x<var; ++x)
	{
		printf("%15s%d","x", x+1);
	}
	for(x=0; x<res; ++x)
	{
		printf("%15s%d", "s", x+1);
	}
	printf("%15s%15s\n", "a", "LD");
	for(x=0; x<res+1;++x)
	{
		for(y=0;y<res+var+2;++y)
		{
			printf("%16lf", matS[x][y]);
		}
		printf("\n");
	}
	printf("");
}
void maximizar(int res, int var, double matR[][res], double matS[res+1][res+var+1])
{
	int x, y, positivo, cp, fp, zop, artificial=0,noptimo=1, i=0, aux=0;
	double mayor, cociente[res+1], menor, pivote, arti[res+1][res+var+2], piporcolumna, suma=0,a;
	for(x=0; x<res;++x)
	{
		if(matR[x][x]==-1)
		{
			artificial=1;
			break;
		}
	}
	/*suma el lado derecho*/
	for(x=0;x<res+1;++x)
	{
		suma+=matS[x][var+res];
	}
	if(artificial==1)
	{
		for(x=0;x<res;++x )
		{
			if(matR[x][x]==-1)
			{
				for(y=0;y<var+res+1;++y)
				{
					if(matS[x+1][y]!=0)
						matS[x+1][y]=-1*matS[x+1][y];
				}
			}
		}
		for(x=0;x<res+1;++x)
		{
			for(y=0;y<var+res+2;++y)
			{
				arti[x][y]=0; /*LLena con ceros la matriz arti*/
			}
		}
		/*Pasa valores de matS a arti y agrega la variable artificial*/
		for(x=0;x<res+1;++x)
		{
			for(y=0;y<var+res;++y)
			{
				arti[x][y]=matS[x][y]; 
			}
		}
		if(suma<50)
			a=-100;
		else
			if(suma>=50  || suma<500)
				a=-1000;
			else
				if(suma>=500  || suma<1500)
					a=-10000;
				else 
					if(1500<=suma)
						a=-100000;
		/*valores de la variable artificial*/
		arti[0][var+res]=a;
		for(x=1;x<res+1;++x)
		{
			arti[x][var+res]=-1;
		}
		/*pasa el LD a la matriz arti*/
		for(x=0; x<res+1;++x)
		{
			arti[x][var+res+1]=matS[x][var+res];
		}
		imprimeSimplexArtificial(res,var, arti);
		i=0;
		aux=0;
		while(noptimo==1 )
		{
			++i;
			zop=0;
			/*busca la columna pivote*/
			mayor=arti[0][0];
			cp=0;
			if(i==1)
			{
				cp=res+var;
			}
			else
			if(i>1)
			{
				for(x=1;x<var+res+1;++x)
				{
				
					if(mayor!=arti[0][x])
					{
						if ( arti[0][x] > mayor)
						{
							cp=x;	
							mayor=arti[0][x];
						}
					}				
					
				}
			}
			/*Divide LD entre columna pivote*/
			cociente[0]=0;
			for(x=1;x<res+1;++x)
			{
				if(i==1)
				{
					if(arti[x][cp]!=0)
					{
						cociente[x]=arti[x][var+res+1]/arti[x][cp];
					}
					else
						cociente[x]=-1;
				}
				else
				{
					if(arti[x][cp]!=0 && arti[x][cp]>0)
					{
						cociente[x]=arti[x][var+res+1]/arti[x][cp];
					}
					else
						cociente[x]=-1;	
				}
			}
			/*busca la fila pivote*/
			menor=cociente[1];
			fp=1;
			for(x=2;x<res+1;++x)
			{
				if(menor!=cociente[x])
				{
					if(i==1)
					{
						if (cociente[x]>=0 && cociente[x] > menor) 
						{
							menor=cociente[x];
							fp=x;
						}
					}
					else
					{
						if(menor<0)
						{
							if (cociente[x]>=0 && cociente[x] > menor) 
							{
								menor=cociente[x];
								fp=x;
							}
						}
						else
							if ( cociente[x]>=0 && cociente[x] < menor) 
							{
								menor=cociente[x];
								fp=x;
							}	
					}
				}
				else
					menor=menor;
			}
			pivote=arti[fp][cp];
			if(pivote<0 && i>1)
			{
				printf("No acotado\n");
				break;
			}
			/*divide la fila entre el pivote*/
			for(x=0; x<res+var+2;++x)
			{
				arti[fp][x]=arti[fp][x]/pivote;
			}

			/*renglon i -pivotei*filapivote*/
			for(x=0;x<res+1;++x)
			{
				piporcolumna=arti[x][cp]; //pivote de la fila 
				for(y=0;y<res+var+2;++y)
				{
					if(x!=fp)
					{
						arti[x][y]=arti[x][y]-(piporcolumna*arti[fp][y]);
					}
				}
			}
			imprimeSimplexArtificial(res,var, arti);
			/*verifica que z sea negativa o igual a cero*/
			for(x=0; x<var+res+1;++x)
			{
				if(arti[0][x]<=0)
				{
					++zop;
				}
				else
					--zop;
			}
			
			if(zop<res+var+1)
				noptimo=1;
			else
				noptimo=0;
			++aux;
			if(aux>=40)
			{
				printf("Alcanzo el numero maximo de iteraciones\n");
				break;
			}
		}	
	}
	else
	{
		imprimeSimplex(res,var, matS);
		aux=0;
		while(noptimo==1 )
		{
			zop=0;
			/*busca la columna pivote*/
			mayor=matS[0][0];
			cp=0;
			for(x=1;x<var+res;++x)
			{
				if(mayor!=matS[0][x])
				{
					if (matS[0][x] > mayor)
					{
						cp=x;	
						mayor=matS[0][x];
					}
				}	
			}
			/*Divide LD entre columna pivote*/
			cociente[0]=0;
			for(x=1;x<res+1;++x)
			{
				if(matS[x][cp]!=0 && matS[x][cp]>0)
				{
						cociente[x]=matS[x][var+res]/matS[x][cp];
				}
				else
					cociente[x]=-1;
			}
			/*busca la fila pivote*/
			menor=cociente[1];
			fp=1;
			for(x=2;x<res+1;++x)
			{
				
				if(menor!=cociente[x])
				{
					if(menor<0)
					{
						if (cociente[x]>=0 && cociente[x] > menor) 
						{
							menor=cociente[x];
							fp=x;
						}
					}
					else
						if ( cociente[x]>=0 && cociente[x] < menor) 
						{
							menor=cociente[x];
							fp=x;
						}	
				}
				else
					menor=menor;
					
			}
			pivote=matS[fp][cp];
			if(pivote<0)
			{
				printf("No acotado\n");
				break;
			}
			/*divide la fila entre el pivote*/
			for(x=0; x<res+var+1;++x)
			{
				matS[fp][x]=matS[fp][x]/pivote;
			}
			/*renglon i -pivotei*filapivote*/
			for(x=0;x<res+1;++x)
			{
				piporcolumna=matS[x][cp]; //pivote de la fila 
				for(y=0;y<res+var+1;++y)
				{
					if(x!=fp)
					{
						matS[x][y]=matS[x][y]-(piporcolumna*matS[fp][y]);
					}
				}
			}
			imprimeSimplex(res,var, matS);
			/*verifica que z sea negativa o igual a cero*/
			for(x=0; x<var+res;++x)
			{
				if(matS[0][x]<=0)
				{
					++zop;
				}
				else
					--zop;
			}
			if(zop<res+var)
				noptimo=1;
			else
				noptimo=0;
			++aux;
			if(aux>=40)
			{
				printf("Alcanzo el numero maximo de iteraciones\n");
				break;
			}
		}
	}
}
void minimizar(int res, int var, double matR[][res], double matS[res+1][res+var+1])
{
	int x, y, positivo, cp, fp, zop, artificial=0,noptimo=1, aux=0, i=0;
	double cociente[res+1], menor, pivote, arti[res+1][res+var+2], piporcolumna, a, suma=0, mayor;
	for(x=0; x<res;++x)
	{
		if(matR[x][x]==-1)
		{
			artificial=1;
			break;
		}
	}
	/*suma el lado derecho*/
	for(x=0;x<res+1;++x)
	{
		suma+=matS[x][var+res];
	}
	
	/*Pone con negativos a z*/
	for(x=0;x<res+var+1;++x)
	{
		if(matS[0][x]!=0)
			matS[0][x]=-1*matS[0][x];
	}
	if(artificial==1)
	{
		/*Multiplica por menos uno los renglones que tienen vaariable de holgura con -1*/
		for(x=0;x<res;++x )
		{
			if(matR[x][x]==-1)
			{
				for(y=0;y<var+res+1;++y)
				{
					if(matS[x+1][y]!=0)
						matS[x+1][y]=-1*matS[x+1][y];
				}
			}
		}
		for(x=0;x<res+1;++x)
		{
			for(y=0;y<var+res+2;++y)
			{
				arti[x][y]=0; /*LLena con ceros la matriz arti*/
			}
		}
		/*Pasa valores de matS a arti y agrega la variable artificial*/
		for(x=0;x<res+1;++x)
		{
			for(y=0;y<var+res;++y)
			{
				arti[x][y]=matS[x][y]; 
			}
		}
		if(suma<50)
			a=-100;
		else
			if(suma>=50  || suma<500)
				a=-1000;
			else
				if(suma>=500  || suma<1500)
					a=-10000;
				else 
					if(1500<=suma)
						a=-100000;
		/*valores de la variable artificial*/
		arti[0][var+res]=a;
		for(x=1;x<res+1;++x)
		{
			arti[x][var+res]=-1;
		}
		/*pasa el LD a la matriz arti*/
		for(x=0; x<res+1;++x)
		{
			arti[x][var+res+1]=matS[x][var+res];
		}
		imprimeSimplexArtificial(res,var, arti);
		i=0;
		while(noptimo==1)
		{
			++i;
			zop=0;
			/*busca la columna pivote*/
			mayor=arti[0][0];
			cp=0;
			if(i==1)
			{
				cp=res+var;
			}
			else
			if(i>1)
			{
				for(x=1;x<var+res+1;++x)
				{
				
					if(mayor!=arti[0][x])
					{
						if ( arti[0][x] > mayor)
						{
							cp=x;	
							mayor=arti[0][x];
						}
					}				
					
				}
			}
			/*Divide LD entre columna pivote*/
			cociente[0]=0;
			for(x=1;x<res+1;++x)
			{
				if(i==1)
				{
					if(arti[x][cp]!=0)
					{
						cociente[x]=arti[x][var+res+1]/arti[x][cp];
					}
					else
						cociente[x]=-1;
				}
				else
				{
					if(arti[x][cp]!=0 && arti[x][cp]>0)
					{
						cociente[x]=arti[x][var+res+1]/arti[x][cp];
					}
					else
						cociente[x]=-1;	
				}
			}
			/*busca la fila pivote*/
			menor=cociente[1];
			fp=1;
			for(x=2;x<res+1;++x)
			{
				if(menor!=cociente[x])
				{
					if(i==1)
					{
						if (cociente[x]>=0 && cociente[x] > menor) 
						{
							menor=cociente[x];
							fp=x;
						}
					}
					else
					{
						if(menor<0)
						{
							if (cociente[x]>=0 && cociente[x] > menor) 
							{
								menor=cociente[x];
								fp=x;
							}
						}
						else
							if ( cociente[x]>=0 && cociente[x] < menor) 
							{
								menor=cociente[x];
								fp=x;
							}	
					}
				}
				else
					menor=menor;
			}
			pivote=arti[fp][cp];
			if(pivote<0 && i>1)
			{
				printf("No acotado\n");
				break;
			}
			/*divide la fila entre el pivote*/
			for(x=0; x<res+var+2;++x)
			{
				arti[fp][x]=arti[fp][x]/pivote;
			}

			/*renglon i -pivotei*filapivote*/
			for(x=0;x<res+1;++x)
			{
				piporcolumna=arti[x][cp]; //pivote de la fila 
				for(y=0;y<res+var+2;++y)
				{
					if(x!=fp)
					{
						arti[x][y]=arti[x][y]-(piporcolumna*arti[fp][y]);
					}
				}
			}
			imprimeSimplexArtificial(res,var, arti);
			/*verifica que z sea negativa o igual a cero*/
			for(x=0; x<var+res+1;++x)
			{
				if(arti[0][x]<=0)
				{
					++zop;
				}
				else
					--zop;
			}
			
			if(zop<res+var+1)
				noptimo=1;
			else
				noptimo=0;
			++aux;
			if(aux>=40)
			{
				printf("Alcanzo el numero maximo de iteraciones\n");
				break;
			}
		}	
	}
	else
	{
		imprimeSimplex(res,var, matS);
		i=0;
		while(noptimo==1)
		{
			++i,
			zop=0;
			/*busca la columna pivote*/
			mayor=matS[0][0];
			cp=0;
			if(i==1)
			{
				mayor=matS[0][0];
				cp=0;
				for(x=1;x<var+res;++x)
				{
					if(mayor!=matS[0][x])
					{
						if (matS[0][x] < mayor)
						{
							cp=x;	
							mayor=matS[0][x];
						}
					}
					
				}
			}
			else
			if(i>1)
			{
				for(x=1;x<var+res;++x)
				{
				
					if(mayor!=matS[0][x])
					{
						if ( matS[0][x] > mayor)
						{
							cp=x;	
							mayor=matS[0][x];
						}
					}				
					
				}
			}
			
			/*Divide LD entre columna pivote*/
			cociente[0]=0;
			for(x=1;x<res+1;++x)
			{
				if(matS[x][cp]!=0 && matS[x][cp]>0)
				{
						cociente[x]=matS[x][var+res]/matS[x][cp];
				}
				else
					cociente[x]=-1;
			}
			/*busca la fila pivote*/
			menor=cociente[1];
			fp=1;
			for(x=2;x<res+1;++x)
			{
				if(menor!=cociente[x])
				{
					if(menor<0)
					{
						if (cociente[x]>=0 && cociente[x] > menor) 
						{
							menor=cociente[x];
							fp=x;
						}
					}
					else
						if ( cociente[x]>=0 && cociente[x] < menor) 
						{
							menor=cociente[x];
							fp=x;
						}	
				}
				else
					menor=menor;
			}
			
			pivote=matS[fp][cp];
			if(pivote<0)
			{
				printf("No acotado\n");
				break;
			}
			/*divide la fila entre el pivote*/
			for(x=0; x<res+var+1;++x)
			{
				matS[fp][x]=matS[fp][x]/pivote;
			}

			/*renglon i -pivotei*filapivote*/
			for(x=0;x<res+1;++x)
			{
				piporcolumna=matS[x][cp]; //pivote de la fila 
				for(y=0;y<res+var+1;++y)
				{
					if(x!=fp)
					{
						matS[x][y]=matS[x][y]-(piporcolumna*matS[fp][y]);
					}
				}
			}
			imprimeSimplex(res,var, matS);
			/*verifica que z sea negativa o igual a cero*/
			for(x=0; x<var+res;++x)
			{
				if(matS[0][x]<=0)
				{
					++zop;
				}
				else
					--zop;
			}
			if(zop<res+var)
				noptimo=1;
			else
				noptimo=0;
				++aux;
			if(aux>=40)
			{
				printf("Alcanzo el numero maximo de iteraciones\n");
				break;
			}
		}	
	}
}
int main()
{
	datos();
	system("pause");
	system("cls");
	int var, res; //var son las variables de decision y res son las restricciones
	datos(&var, &res);
	double matV[res][var], matR[res][res], ld[res], z[var], matS[res+1][res+var+1];
	// matV es la matriz de los varoles de las restricciones
	// matR es la matriz de las variables de holgura
	// ld es el vestor que va a guardar el LadoDerecho
	// z es la funcion ofjetivo
	// matS va a guardar todos los datos
	fflush(stdin);
	system("cls");
	ingresoDatos(res, var, matV, matR, ld, z);
	unir(res, var, matV, matR, ld, z, matS);
	imprimeMat(res, var, matS);
	int op;
	printf("\n\nDeseas: \n1)...Maximizar\n2)...Minimizar\nDigite opcion[1,2]: ");
	do
	{
		scanf("%d", &op);
		if(op<1 || op>2)
			printf("Digite 1 o 2: ");
	}while(op<1 || op>2);
	system("pause");
	system("cls");
	switch(op)
	{
		case 1:
			maximizar(res, var, matR, matS);
		break;
		case 2:
		 	minimizar(res, var, matR, matS);
		break;
	}
	return 0;
}


