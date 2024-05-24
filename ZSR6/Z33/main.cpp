template <typename TipEl, template <typename...> class Kontejner = std::vector>   class Tok
{
    Kontejner<TipEl> kolekcija;
public:
    template <typename TipEl2, template <typename...> class Kontejner2>       friend class Tok; // Stvara prijateljstvo između različitih vrsta tokova
    template <typename IterTip>       Tok(IterTip pocetak, const IterTip iza_kraja);
    template <typename IterabilniKontejner>       Tok(const IterabilniKontejner &kontejner);
    Tok(std::initializer_list<TipEl> lista);
    static Tok<TipEl, Kontejner> Opseg(TipEl poc, TipEl kraj, TipEl korak = 1);
    unsigned int Velicina() const;
    bool Prazan() const;
    Tok<TipEl, Kontejner> Limitiraj(unsigned int n) const;
    Tok<TipEl, Kontejner> Preskoci(unsigned int n) const;
    Tok<TipEl, Kontejner> Obrnut() const;
    Tok<TipEl, Kontejner> Akcija(std::function<void(void)> akcija) const;
    void ZaSvaki(std::function<void(TipEl)> akcija) const;
    Tok<TipEl, Kontejner> Filtriraj(std::function<bool(TipEl)> predikat) const;
    TipEl PronadjiPrvi() const;
    TipEl PronadjiPosljednji() const;
    bool ZadovoljavaBaremJedan(std::function<bool(TipEl)> kriterij) const;
    bool ZadovoljavaNijedan(std::function<bool(TipEl)> kriterij) const;
    bool ZadovoljavajuSvi(std::function<bool(TipEl)> kriterij) const;
    TipEl Akumuliraj(TipEl inicijalna,        std::function<TipEl(TipEl, TipEl)> akumulator) const;
    TipEl Akumuliraj(std::function<TipEl(TipEl, TipEl)> akumulator) const;
    Tok<TipEl, Kontejner> Sortirano(std::function<bool(TipEl, TipEl)> komparator        = [](TipEl x, TipEl y)
    {
        return x < y;
    }) const;
    Tok<TipEl, Kontejner> Unikatno(std::function<bool(TipEl, TipEl)> komparator        = [](TipEl x, TipEl y)
    {
        return x == y;
    }) const;
    Tok<TipEl, Kontejner> Proviri(std::function<void(TipEl)> akcija) const;
    TipEl Minimalan(std::function<bool(TipEl, TipEl)> komparator        = [](TipEl x, TipEl y)
    {
        return x < y;
    }) const;
    TipEl Maksimalan(std::function<bool(TipEl, TipEl)> komparator        = [](TipEl x, TipEl y)
    {
        return x > y;
    }) const;
    template <typename Kont2>       Kont2 Sakupi(std::function<void(Kont2 &, TipEl)> kombinator) const;
    template <typename TipEl2>       Tok<TipEl2, Kontejner> Mapiraj(std::function<TipEl2(TipEl)> maper) const;
    template <typename TipEl2>       Tok<TipEl2, Kontejner> MapirajPoravnato(          std::function<Tok<TipEl2, Kontejner>(TipEl)> maper) const;
};
