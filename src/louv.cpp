#include "graph.h"
#include "graph_binary.h"
#include <unistd.h>
#include "louvain.h"
#include "shimalik.h"

using namespace std;
Quality *q;
int kmin = 6;
int levels = -1;
long double precision = 0.000001L;
int display_level = -1;

void
display_time(const char *str) {
    time_t rawtime;
    time ( &rawtime );
    cerr << str << ": " << ctime (&rawtime);
}

extern "C" {
    void runLouvain(double* edge_list, int n_rows) {
        display_time("converting edge_list");
        GraphCreator g(edge_list, n_rows);
        display_time("converting done");
        g.clean(0);
        display_time("cleaning done");
        g.renumber(0, "temp/graph.relation");
        display_time("renumbering done");
        g.display_binary("temp/graph.bin", "temp/graph.weights", 0);
        display_time("binary written");

        display_time("starting louvain");
        Graph g_bin("temp/graph.bin", "temp/graph.weights", 0);
        display_time("graph created from binary");
        //Graph g_bin(g.links);
        //g.links.resize(0);
        q = new ShiMalik(g_bin, kmin);
        cerr << endl << "Computation of communities with the " << q->name << " quality function" << endl << endl;
        Louvain c(-1, precision, q);
        
        bool improvement = true;
        long double quality = (c.qual)->quality();
        long double new_qual;
        int level = 0;
        
        do {
            cerr << "level " << level << ":\n";
            display_time("  start computation");
            cerr << "  network size: "
                << (c.qual)->g.nb_nodes << " nodes, "
                << (c.qual)->g.nb_links << " links, "
                << (c.qual)->g.total_weight << " weight" << endl;
        
            cerr << "improving" << endl;
            improvement = c.one_level();
            cerr << "new qual" << endl;
            new_qual = (c.qual)->quality();
        
            cerr << "level up" << endl;
            if (++level==display_level)
              (c.qual)->g.display();
            if (display_level==-1)
              c.display_partition();
            //++level;
            //(c.qual)->g.display();
            //cerr << "displaying" << endl;
            //c.display_partition();
        
            cerr << "paritioning" << endl;
            g_bin = c.partition2graph_binary();
            delete q;
            cerr << "shimalik" << endl;
            q = new ShiMalik(g_bin, kmin);
            cerr << "new louv" << endl;
            c = Louvain(-1, precision, q);
            cerr << "  quality increased from " << quality << " to " << new_qual << endl;
        
            quality = new_qual;
        
            display_time("  end computation");
        
        } while(improvement);
        
        display_time("End");
        cerr << new_qual << endl;
        
        delete q;
    }
}
