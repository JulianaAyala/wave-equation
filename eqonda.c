//
//  eqonda.c
//  
//
//  Created by Juliana Ayala on 4/22/14.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void copy(float *donde, float *loque, int n);

int main(){

    /* inicializo las variables a usar*/
    int n=1000;
    float *x=malloc(n*sizeof(float));
    float *uinicial=malloc(n*sizeof(float));
    float *ufuturo=malloc(n*sizeof(float));
    float *upasado=malloc(n*sizeof(float));
    float *upresente=malloc(n*sizeof(float));
    int i,p;
    float paso;
    FILE *output;
    FILE *out;
    
    /*creo archivos los cuales van a guardar los datos para la animacion*/
    char filename1[20]="datos_eqonda.dat";
    output=fopen(filename1,"a");
    
    char filename[20]="datos_iniciales.dat";
    out=fopen(filename,"a");
    
    /*lleno las listas con los datos iniciales para tener la grafica de estos, para esto los guardo en un archivo aparte*/
    
    for(i=0;i<n;i++){
        paso = 1.0/n;
        x[i]=i*paso;
        uinicial[i] = exp(-((x[i]-0.3)*(x[i]-0.3))/0.01);
        
        fprintf(out, "%f %f\n", x[i], uinicial[i]);
        
    }
    
    /*para encontrar las iteraciones con condiciones iniciales*/
    float delta_x = 1.0/n;
    float delta_t = 0.0005;
    float c=1.0;
    
    float r=c*delta_t/delta_x;
    
    uinicial[0]=0.0;
    uinicial[n-1]=0.0;
    
    ufuturo[0]=0.0;
    ufuturo[n-1]=0.0;
    
    printf("%f %f %f\n", delta_x, delta_t,r);
    
    for(i=1;i<n-1;i++){
        ufuturo[i] = uinicial[i] + (pow(r,2)/2.0) * (uinicial[i+1] - 2.0 * uinicial[i] + uinicial[i-1]);
    }
    
    /*creo variables nuevas para guardar el valor anterior*/
    copy(upasado, uinicial, n);
    copy(upresente, ufuturo, n);
        
    /*siguientes iteraciones*/
    int n_time = 1000;
    
    for(p=0;p<n_time;p++){
        for(i=0;i<n;i++){
            ufuturo[i] = (2.0*(1.0-pow(r,2)))*upresente[i] - upasado[i] + (pow(r,2))*(upresente[i+1] +  upresente[i-1]);
            fprintf(output, "%f ", upresente[i]);
        }
        fprintf(output,"\n");
        copy(upasado, upresente, n);
        copy(upresente, ufuturo, n);
    }


    fclose(output);
    fclose(out);
   
    return 0;
}

void copy(float *donde, float *loque, int n){
    int i;
    for(i=0;i<n;i++){
        donde[i] = loque[i];
    }
}

