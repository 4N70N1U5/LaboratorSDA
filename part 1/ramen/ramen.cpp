// Complexitate: O(N * log N)
// 
// Pentru a rezolva problema, am ales sa folosesc un BST pentru
// ca rezolvarea implica multe cautari succesive, pe care vreau
// sa le fac intr-un timp cat mai scurt. Pentru implementarea BST,
// folosesc set din STL.
// 
// In primul rand, citesc din fisier toate comenzile, le retin,
// si determin toate momentele in care vor fi plasate pe banda
// portiile, adunand timpul constant de prepare, si pe acestea
// le introduc in BST. Comenzile le stochez intr-un vector,
// pentru ca va trebui sa le parcurg pe toate pentru a determina
// momentul in care fiecare client va manca pentru comanda respectiva.
// Folosind un struct retin despre comanda momentul in care a fost
// plasata, numarul scaunului clientului si numarul de ordine al
// comenzii, pentru ca acestea vor fi reordonate.
// 
// Comenzile le voi sorta in vector dupa distanta clientului fata
// de bucatarie, deoarece fiecare client va lua o portie de pe banda
// cat de repede posibil, asa ca un client asezat mai aproape de
// bucatarie va avea "prioritate" fata de unul asezat mai departe.
// Comenzile aceluiasi client vor fi ordonate, bineinteles, in ordinea
// plasarii.
// 
// In al doilea rand, pentru a determina momentele in care se va manca,
// voi parcurge comenzile in ordinea sortarii, si pentru fiecare comanda
// voi cauta in BST prima comanda care va aparea in fata scaunului
// clientului. Pentru asta, trebuie sa determin care este cea mai recenta
// comanda plasata pe banda, care nu a depasit inca scaunul clientului.
// Ca sa nu depaseasca clientul, o comanda trebuie sa nu fi fost plasata
// pe banda mai devreme decat valoarea obtinuta din scaderea distantei
// fata de bucatarie din momentul plasarii comenzii. Apoi, caut in BST 
// prima valoare mai mare sau egala cu aceasta valoare folosind
// lower_bound. Obtin astfel momentul in care portia de ramen care va fi
// mancata pentru acea comanda a fost plasata pe banda, si ca sa determin
// momentul in care se va manca, adun la aceasta valoare distanta fata de
// de bucatarie, adica timpul necesar ca portia sa ajunga la client.
// Portia respectiva este apoi stearsa din BST.

#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

ifstream fin("ramen.in");
ofstream fout("ramen.out");

struct comanda
{
    long long secunda_plasare, numar_scaun, numar_ordine;

    // Sortez comenzile dupa pozitia scaunului si abia apoi
    // dupa secunda la care a fost plasata comanda, deoarece
    // comenzile pot fi ridicate de un alt client decat cel
    // ce a plasat-o, asa ca trebuie sa stiu prin fata caror
    // clienti trec mai intai acestea.
    bool operator<(const comanda &aux) const
    {
        if (numar_scaun == aux.numar_scaun)
            return secunda_plasare < aux.secunda_plasare;

        return numar_scaun < aux.numar_scaun;
    }
};

long long n, d;
vector<long long> raspuns;
vector<comanda> comenzi;
set<long long> comenzi_pregatite;

int main()
{
    fin >> n >> d;

    raspuns.resize(n);

    for (int i = 0; i < n; i++)
    {
        comanda aux;
        fin >> aux.secunda_plasare >> aux.numar_scaun;

        aux.numar_ordine = i;
    
        // Retin comenzile intr-un vector pentru a le putea sorta.
        comenzi.push_back(aux);

        // Introduc timpii la care portiile de ramen sunt pregatite
        // si plasate pe banda in BST.
        comenzi_pregatite.insert(aux.secunda_plasare + d);
    }

    sort(comenzi.begin(), comenzi.end());

    for (comanda c : comenzi)
    {
        // Caut in BST prima comanda care a fost plasata pe banda,
        // dar care nu a depasit inca scaunul clientului. Acesta o
        // va ridica abia dupa ce aceasta a parcurs drumul pana la
        // el, deci adun numarul de ordin al scaunului la valoarea
        // obtinuta din BST, care este secunda cand a fost plasata
        // pe banda comanda.
        raspuns[c.numar_ordine] = *comenzi_pregatite.lower_bound(c.secunda_plasare - c.numar_scaun) + c.numar_scaun;

        // Sterg comanda ridicata din BST.
        comenzi_pregatite.erase(comenzi_pregatite.lower_bound(c.secunda_plasare - c.numar_scaun));
    }

    for (int i = 0; i < n; i++)
    {
        fout << raspuns[i] << '\n';
    }
}
