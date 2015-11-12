#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int r, g, b;
} pixel;

pixel imagem[3698][3698], imagem2[3698][3698];

int main(int argc, char *argv[]) {

	char magic[3],coments[39],enter,c,d[4],e[4];
	int col, lin;
	int branco, blur, somar, ver,verifica=0, somag, somab, cont;
	int i, j, k, l;
	FILE *fe, *fs;


        for (i=0;i<3698;i++){
			for (j=0;j<3698;j++){
				imagem[i][j].r= -1;
				imagem[i][j].g= -1;
				imagem[i][j].b= -1;
				imagem2[i][j].r= -1;
				imagem2[i][j].g= -1;
				imagem2[i][j].b= -1;
			}
		}


        blur = atoi(argv[1]);

        if ((fe=fopen(argv[2],"r+"))!=NULL){
            fscanf(fe,"%s", magic);
            i=0;
            fscanf(fe,"%c",&enter);
            fscanf(fe,"%c",&c);
            while (c != '\n'){
                    coments[i]=c;
                    fscanf(fe,"%c",&c);
                    i++;
            }
            coments[i]='\0';
            if (coments[0]=='#'){
                fscanf(fe,"%d %d", &col, &lin);
            }
            else {
                i=0;
                while (coments[i]>47 && coments[i]<58){
                    d[i]=coments[i];
                    i++;
                    printf("%c",coments[i-1]);
                }
                i++;
                ver=i;
                while (coments[i]!= '\0'){
                    e[i-ver]=coments[i];
                    i++;
                }
                col=atoi(d);
                lin=atoi(e);
            }
            fscanf(fe,"%d", &branco);
			for (i=blur; i<(lin+blur); i++) {
                for (j=blur; j<(col+blur); j++) {
                        fscanf(fe,"%d%d%d", &imagem[i][j].r,
                                    &imagem[i][j].g,
                                    &imagem[i][j].b);
                }
            }
            fclose(fe);
            for (i=blur; i<(lin+blur); i++) {
                for (j=blur; j<(col+blur); j++) {
                    if (imagem[i][j].r!=-1){
                        somar=0;
                        somag=0;
                        somab=0;
                        cont=0;
                        for (k=i-blur;k<=i+blur;k++){
                            for (l=j-blur;l<=j+blur;l++){
								if (imagem[k][l].r!=-1){
									somar+=imagem[k][l].r;
									somag+=imagem[k][l].g;
									somab+=imagem[k][l].b;
									cont++;
								}
							}
                        }
                        imagem2[i][j].r=somar/cont;
                        imagem2[i][j].g=somag/cont;
                        imagem2[i][j].b=somab/cont;
                    }
                }
            }
            fs=fopen(argv[3],"w+");

                fprintf(fs,"%s\n", magic);
                fprintf(fs,"%d %d\n", col, lin);
                fprintf(fs,"%d\n", branco);

                for (i=blur; i<(lin+blur); i++) {
                    for (j=blur; j<(col+blur); j++) {
                            if (imagem2[i][j].r!=-1)
                                fprintf(fs,"%d\n%d\n%d\n", imagem2[i][j].r,
                                        imagem2[i][j].g,
                                        imagem2[i][j].b);
                    }
                }

            fclose(fs);
        }
        else printf("O arquivo %s nao foi encontrado!!",argv[2]);
return 0;
}
