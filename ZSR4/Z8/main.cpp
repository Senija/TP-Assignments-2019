void Sortiraj(std::function<bool(const TipElemenata &, const TipElemenata &)> kriterij = std::less<TipElemenata>())
{
    tok.seekg(0, std::ios::end);
    auto kraj = tok.tellg();
    int broj_el=tok.tellg()/sizeof(TipElemenata);
    TipElemenata element1, element2;
    for(int i=0; i<broj_el; i++) {
        tok.seekg(i*sizeof(TipElemenata), std::ios::beg);
        if(!tok.read(reinterpret_cast<char*>(&element1), sizeof(TipElemenata))) throw std::logic_error("Problemi prilikom pristupa datotecii");
        TipElemenata pomocni=element1;
        int pozicija=tok.tellg(), pomoc_poz=tok.tellg();
        for(int j=i+1; j<broj_el; j++) {
            tok.seekg(j*sizeof(TipElemenata), std::ios::beg);
            pomoc_poz=tok.tellg();
            if(!tok.read(reinterpret_cast<char*>(&element2), sizeof(TipElemenata))) throw std::logic_error("Problemi prilikom pristupa datoteci");
            if(!kriterij(pomocni,element2)) {
                pomocni=element2;
                pozicija=pomoc_poz;
            }
        }
        if(pomocni != element1) {
            tok.seekp(i*sizeof(TipElemenata), std::ios::beg);
            if(tok.tellg()==kraj) continue;
            tok.write(reinterpret_cast<char*>(&pomocni), sizeof(TipElemenata));
            tok.seekp(pozicija, std::ios::beg);
            if(tok.tellg()==kraj) continue;
            tok.write(reinterpret_cast<char*>(&element1), sizeof(TipElemenata));
        }
    }
}
