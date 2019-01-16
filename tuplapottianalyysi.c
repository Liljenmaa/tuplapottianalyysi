#include <stdio.h>
#include <stdlib.h>

#define KELAPITUUS 24

char kelaPaikka(const char * kela, int indeksi, int vaihto)
{
    if (indeksi + vaihto >= KELAPITUUS)
        return kela[indeksi + vaihto - KELAPITUUS];
    
    else
        return kela[indeksi + vaihto];
}

double riviAnalyysi(const char * kela1, int i, int v1, const char * kela2, int j, int v2, const char * kela3, int k, int v3)
{
    //kkm || --m 
    if (kelaPaikka(kela3, k, v3) == 'm')
    {
        //kkm
        if (kelaPaikka(kela1, i, v1) == 'k' &&
            kelaPaikka(kela2, j, v2) == 'k')
            return 1.60;
        
        //--m
        else
            return 0.80;
    }
        
    //kkk || kk- || k--
    else if (kelaPaikka(kela1, i, v1) == 'k')
    {
        //kkk || kk-
        if (kelaPaikka(kela2, j, v2) == 'k')
        {
            //kkk
            if (kelaPaikka(kela3, k, v3) == 'k')
                return 1.60;
            
            //kk-
            else
                return 0.80;
        }
        
        //k--
        else
            return 0.40;
    }
    
    //täys- ja puolrivitarkistus (ilman kirsikoita)
    else if (kelaPaikka(kela1, i, v1) == kelaPaikka(kela2, j, v2))
    {
        //täysrivi
        if (kelaPaikka(kela2, j, v2) == kelaPaikka(kela3, k, v3))
        {
            //RAY
            if (kelaPaikka(kela1, i, v1) == 'I')
                return 10.00;
            
            //ray
            else if (kelaPaikka(kela1, i, v1) == 'P')
                return 4.00;
            
            //ppp
            else if (kelaPaikka(kela1, i, v1) == 'p')
                return 3.00;
            
            //vvv
            else if (kelaPaikka(kela1, i, v1) == 'v')
                return 3.00;
            
            //rrr
            else if (kelaPaikka(kela1, i, v1) == 'r')
                return 3.00;
            
            //lll
            else if (kelaPaikka(kela1, i, v1) == 'l')
                return 2.00;
            
            //aaa
            else if (kelaPaikka(kela1, i, v1) == 'a')
                return 1.60;
        }
    
        //puolrivi
        else if (kelaPaikka(kela3, k, v3) == 't')
        {
            //IIt (ei voittoa)
            if (kelaPaikka(kela1, i, v1) == 'I')
                return 0.00;
            
            //PPt
            else if (kelaPaikka(kela1, i, v1) == 'P')
                return 3.00;
                
            //ppt
            else if (kelaPaikka(kela1, i, v1) == 'p')
                return 2.00;
            
            //vvt
            else if (kelaPaikka(kela1, i, v1) == 'v')
                return 2.00;
            
            //rrt
            else if (kelaPaikka(kela1, i, v1) == 'r')
                return 2.00;
            
            //llt
            else if (kelaPaikka(kela1, i, v1) == 'l')
                return 2.00;
            
            //aat
            else if (kelaPaikka(kela1, i, v1) == 'a')
                return 1.60;
        }
    }
    
    //ei voittoa
    else
        return 0.00;
}

double linjaAnalyysi(const char * kela1, const char * kela2, const char * kela3, int i, int j, int k, int linja)
{
    if (linja == 1)
        return riviAnalyysi(kela1, i, 1, kela2, j, 1, kela3, k, 1);
    
    else if (linja == 2)
        return riviAnalyysi(kela1, i, 2, kela2, j, 2, kela3, k, 2);
    
    else if (linja == 3)
        return riviAnalyysi(kela1, i, 0, kela2, j, 0, kela3, k, 0);
    
    else if (linja == 4)
        return riviAnalyysi(kela1, i, 2, kela2, j, 1, kela3, k, 0);
    
    else if (linja == 5)
        return riviAnalyysi(kela1, i, 0, kela2, j, 1, kela3, k, 2);
}

double kelaAnalyysi(const char * kela1, const char * kela2, const char * kela3, int i, int j, int k)
{
    int linja = 1;
    double suurinKerroin = 0;
    double nytKerroin;
    double lopullinenKerroin;
    int osumat = 0;
    
    for (linja = 1; linja < 6; ++linja)
    {
        nytKerroin = linjaAnalyysi(kela1, kela2, kela3, i, j, k, linja);
        
        if (nytKerroin > 0.1)
        {
            osumat += 1;
            suurinKerroin = (nytKerroin > suurinKerroin ? nytKerroin : suurinKerroin);
        }
    }
    
    lopullinenKerroin = osumat * suurinKerroin;
    return lopullinenKerroin;
}

int main(void)
{
    const char I = 'I';
    const char P = 'P';
    const char v = 'v';
    const char l = 'l';
    const char r = 'r';
    const char p = 'p';
    const char a = 'a';
    const char k = 'k';
    const char m = 'm';
    const char t = 't';
    
    const char kela1[] = {P,p,v,I,p,v,l,v,p,v,I,P,l,v,I,l,p,k,a,I,l,P,r,P};
    const char kela2[] = {I,v,k,r,p,k,l,v,l,P,r,v,v,p,r,a,I,l,v,l,k,r,P,a};
    const char kela3[] = {l,v,v,I,l,t,P,m,t,I,a,p,r,v,t,I,r,k,t,p,r,I,t,P};

    int ind1 = 0;
    int ind2 = 0;
    int ind3 = 0;
    
    FILE * kaikkiKelat;
    FILE * paavoitot;
    
    double kerroin;
    int paavoittoja = 0;
    
    kaikkiKelat = fopen("KaikkiKelat.txt", "w");
    paavoitot = fopen("Päävoitot.txt", "w");
    
    for (ind1 = 0; ind1 < KELAPITUUS; ++ind1)
    {
        for (ind2 = 0; ind2 < KELAPITUUS; ++ind2)
        {
            for (ind3 = 0; ind3 < KELAPITUUS; ++ind3)
            {
                kerroin = kelaAnalyysi(kela1, kela2, kela3, ind1, ind2, ind3);
                fprintf(kaikkiKelat, "%.2d, %.2d, %.2d: %.2f kerroin\n", ind1, ind2, ind3, kerroin);
                
                if ((int)kerroin == 50)
                {
                    paavoittoja += 1;
                    fprintf(paavoitot, "%.2d, %.2d, %.2d: %.2f kerroin\n", ind1, ind2, ind3, kerroin);
                }
            }
        }
    }
    
    fclose(kaikkiKelat);
    
    fprintf(paavoitot, "\nPäävoittoja: %d\n", paavoittoja);
    
    fclose(paavoitot);
    
    printf("Tiedostot KaikkiKelat.txt ja Päävoitot.txt (toivottavasti) luotu, tarkista juurikansio.\n");
    
    return 0;
}
