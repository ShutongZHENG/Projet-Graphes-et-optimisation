//
//  Graph.cpp
//  Prim
//
//  Created by ZHENG Shutong on 2022/10/10.
//

#include "Graph.hpp"





/// Description
///Ajoutez des arêtes au graphique et supprimez automatiquement les doublons redondants si des doublons sont trouvés.
///Par exemple Edge("S1", "T1",2) , Edge("T1", "S1",2) n'en conservera qu'un seul
/// - Parameter e: e  est  arêtes
void Graph:: addEdge(Edge e){
    bool existEdge = false;
    for(int i = 0 ; i < edges.size(); i++){
        if(edges[i].getWeight() == e.getWeight() &&((edges[i].getTo() == e.getTo() && edges[i].getFrom() == e.getFrom()) ||(edges[i].getFrom() == e.getTo() && edges[i].getTo() == e.getFrom())))
            existEdge = true;
    }
    if(!existEdge){
        edges.push_back(e);
        
        bool existNodeFrom = false;
        bool existNodeTo = false;
        for(int i = 0 ; i<nodes.size();i++){
            if(nodes[i].name == e.getFrom())
                existNodeFrom = true;
            if(nodes[i].name == e.getTo())
                existNodeTo = true;
        }
        
        if(!existNodeFrom)
            nodes.push_back({e.getFrom(),false,-1,""});
        if(!existNodeTo)
            nodes.push_back({e.getTo(),false,-1,""});
        
    }
}


/// Description
///- Returns: le nombre d'arêtes
int Graph::nbrEdges(){
    
    return (int)edges.size();
}

vector<Edge> Graph::getAdjacentEdgeList(Node node){
    vector<Edge> res;
    for(int i = 0 ; i< edges.size(); i++){
        if(edges[i].getFrom() == node.name || edges[i].getTo() == node.name )
            res.push_back(edges[i]);
    }
    return res;
    
}



/// Description
/// Tous les nœuds sont-ils sélectionnés?
///- Returns: true : ils sont sélectionnés
///           false : au moins un n'est pas sélectionné
///
bool Graph::allSelected(){
    bool res = true;
    for(int i =0 ; i< nodes.size(); i++){
        if(nodes[i].isSelected == false){
            res = false;
            break;
        }
    }
    
    return res;
}



/// Description
/// Sortie du processus d'algorithme prim dans le terminal
void Graph::printTablePrim(){
    cout<<endl;
    cout <<"         ";
    for(int i =0 ; i< nodes.size(); i++){
        cout << nodes[i].name<< "  ";
        
    }
    cout <<endl;
    
    
    cout <<"selected ";
    for(int i =0 ; i< nodes.size(); i++){
        if(nodes[i].isSelected)
        cout << "T "<< "  ";
        else
            cout << "F "<< "  ";
        
    }
    cout <<endl;
    
    cout <<"Minidis  ";
    for(int i =0 ; i< nodes.size(); i++){
        if(nodes[i].minWeight == -1)
        cout << "0   ";
        else
            cout << nodes[i].minWeight<< "   ";
            
        
    }
    cout <<endl;
    
    
    cout <<"Parent   ";
    for(int i =0 ; i< nodes.size(); i++){
        if(nodes[i].parent == "")
            cout<<"-   ";
        else
        cout << nodes[i].parent<< "  ";
        
    }
    cout <<endl;
    
}


/// Description
/// Trouver les nœuds avec la plus petite somme de poids utilisée dans l'algorithme prim
/// - Returns: indice des nœuds avec une somme de poids minimale
int Graph::getMiniWeightNode(){
    int res = -1;
    for(int i =0 ;i<nodes.size(); i++){
        if(!nodes[i].isSelected){
            if (nodes[i].minWeight != -1 && res == -1)
                res = i;
            if (nodes[i].minWeight < nodes[res].minWeight && nodes[i].minWeight != -1)
                res = i;
                
        }
        
    }
    cout << "will select : "<< nodes[res].name <<endl;
    return res;
    
}


/// Description
/// Calcule le poids minimum du noeud adjacent d'un noeud.
/// Si la valeur miniWeight du nœud adjacent est supérieure au poids du nœud actuel qui lui est connecté. La valeur du poids du noeud adjacent est remplacée. La valeur de Parent est également remplacée par le noeud courant.
/// - Parameters:
///   - index: index description : indice du nœud courant
///   - childrenEdges: childrenEdges description : l'ensemble des nœuds connectés au noeud courant
void Graph::calculMiniWeight(int index, vector<Edge> childrenEdges){
    for(int i =0 ; i< childrenEdges.size(); i++){
        for (int j = 0 ; j < nodes.size();j++ ) {
            if(!nodes[j].isSelected){
                if(nodes[j].name == childrenEdges[i].getTo() || nodes[j].name == childrenEdges[i].getFrom()){
                    if(nodes[j].minWeight == -1 || nodes[j].minWeight > childrenEdges[i].getWeight()){
                        nodes[j].minWeight = childrenEdges[i].getWeight();
                        nodes[j].parent = nodes[index].name;
                    }
                }
                
            }
        }
        
    }
    
}



/// Description
/// Générer un arbre couvrant minimal par l'algorithme prim
void Graph::makeMiniTree(){
    
    if(!nodes.empty()){
         //initialisation
        nodes[0].isSelected = true;
        vector<Edge> childrenEdges = getAdjacentEdgeList(nodes[0]);
        calculMiniWeight(0, childrenEdges);
        printTablePrim();
     

        
        //Boucle à travers tous les nœuds jusqu'à ce que tous les nœuds soient sélectionnés pour terminer la boucle.
        while (!allSelected()) {
            
            int currentIndex = getMiniWeightNode();
            nodes[currentIndex].isSelected = true;
            vector<Edge> childrenEdges =  getAdjacentEdgeList(nodes[currentIndex]);
            calculMiniWeight(currentIndex, childrenEdges);   // O(m*n)
            printTablePrim();


        }

        for(int i = 0 ; i < nodes.size(); i++){
            if(nodes[i].minWeight != -1){
                miniTree.push_back(Edge(nodes[i].parent, nodes[i].name, nodes[i].minWeight));
            }


        }
        
        
    }
    
}

/// Description
/// Trier l'arbre couvrant minimum, par ordre décroissant selon la valeur de poids
void Graph::sortMiniTree(){
    int nbrEdges = (int)miniTree.size();
    for(int i = 0 ; i< nbrEdges-1; i++){
        for(int j=0 ; j < nbrEdges-1-i;j++){
            if(miniTree[j].getWeight() < miniTree[j+1].getWeight()){
                Edge tmp = miniTree[j+1];
                swap(miniTree[j], miniTree[j+1]);
                
            }
            
        }
        
    }
    
}



/// Description
/// Sous-programme récursif. Vérifier si un noeud peut avoir au moins un S qui lui est connecté directement ou indirectement par récursivité
/// - Parameters:
///   - node:  node description : Nœud à vérifier
///   - edges: edges description : ensemble d'arètes
/// - Returns : true : noeud peut communiquer avec s
///            false : sinon
bool Graph::sous_allTtoS(Node node, vector<Edge> edges){
    
    if(node.name.find("S") != string::npos  )
        return true;
    else{
        vector<Edge> edgesAboutNode;
        for(int i = 0; i<edges.size();i++){
            if(edges[i].getTo() == node.name || edges[i].getFrom() == node.name){
                edgesAboutNode.push_back(edges[i]);
            }
        }
        if (edgesAboutNode.size() == 0)
            return false;
        
        
        

        
        bool res = false;
        for(int i = 0 ; i < edgesAboutNode.size(); i++){
            Node nextNode;
            if(edgesAboutNode[i].getFrom() != node.name){
                nextNode = {edgesAboutNode[i].getFrom(),true, -1,""};
                
            }else{
                nextNode = {edgesAboutNode[i].getTo(),true,-1,""};
            }
            
            int index_s ;
            for(int j =0 ;j<edges.size();j++){
                if(edges[j].getFrom() == node.name && edges[j].getTo() == nextNode.name  )
                    index_s = j;
                if (edges[j].getTo() == node.name && edges[j].getFrom() == nextNode.name )
                    index_s = j;
            }
            vector<Edge> nextEdges  = edges;
            nextEdges.erase(nextEdges.begin()+index_s);
            res = res || sous_allTtoS(nextNode, nextEdges);
            
        }
        return res;
        
        
    }
 
}

/// Description
/// Voir si tous les T ont au moins un S qui peut communiquer
/// - Parameter edges: edges description : ensemble d'arètes
/// - Returns : true : ils peuvent tous communiquer
///            false : sinon
bool Graph::allTtoS(vector<Edge> edges){
    bool res = true;
    
    for(int i = 0 ; i<nodes_t.size(); i++){
        res = res && sous_allTtoS(nodes_t[i], edges);
        
    }
    


    return res;
}

/// Description
/// Arbre couvrant minimum généré Économique : Chaque T ne peut être connecté directement ou indirectement qu'à un S
void Graph::makeMiniTree_Economic(){
    sortMiniTree();
    int nbrS = 0;
    int nbrComponent = 0;
    int indexEdge = 0;
    vector<Edge> cuttedEdges = miniTree;
    for(int i = 0 ; i< nodes.size(); i++)
        if(nodes[i].name.find("S") != string::npos){
            nbrS++;
            nodes_s.push_back(nodes[i]);
        }
            
        else
            nodes_t.push_back(nodes[i]);

    
    while (nbrComponent < nbrS-1 && indexEdge < cuttedEdges.size()) {
     
        vector<Edge> tmpEdges ;
        for(int i = 0 ; i<cuttedEdges.size(); i++){
            if(i != indexEdge )
                tmpEdges.push_back(cuttedEdges[i]);
        }
    
        if(allTtoS(tmpEdges)){
            nbrComponent++;
            cuttedEdges = tmpEdges;
           // indexEdge--;
        }else{
            indexEdge++;
          
        }
    }
    
    

    
    
    for(int i = 0 ; i< nodes_s.size() ; i++){
        
        deque<string> nodes_tmp;
        nodes_tmp.push_back(nodes_s[i].name);
        vector<Edge> edges_tmp;
        while (nodes_tmp.size() !=0 ) {
           
            for(int j = 0; j< cuttedEdges.size(); j++){
                if(nodes_tmp[0]== cuttedEdges[j].getFrom() ){
                    nodes_tmp.push_back(cuttedEdges[j].getTo());
                    edges_tmp.push_back( cuttedEdges[j]);
                    cuttedEdges.erase(cuttedEdges.begin()+j);
                    j--;
                }
                if( nodes_tmp[0] == cuttedEdges[j].getTo()){
                    nodes_tmp.push_back(cuttedEdges[j].getFrom());
                    edges_tmp.push_back( cuttedEdges[j]);
                    cuttedEdges.erase(cuttedEdges.begin()+j);
                    j--;
                }
                
                
            }
            if(nodes_tmp.size() == 1 && nodes_tmp[0] == nodes_s[i].name )
                edges_tmp.push_back( Edge(nodes_tmp[0], "", -1));
            nodes_tmp.pop_front();
            
            
            
            
            
        }
        
        miniTree_Economic.push_back(edges_tmp);

    }
    
    
    for(int i = 0; i< miniTree_Economic.size(); i++){
        cout << endl;
        cout<<"Connected Component "<< i+1 << ": "<<endl;
        for(int j = 0 ; j <miniTree_Economic[i].size();j++){
            cout<< miniTree_Economic[i][j].getFrom() << "-----"<<miniTree_Economic[i][j].getTo() <<"    ";
            
        }
        cout << endl;
    }
        
    
    
    
}
