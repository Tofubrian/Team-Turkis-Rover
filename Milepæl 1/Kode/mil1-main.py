'''
Main kode til milepæl 1.
'''
def beregn_renteindtægt_og_abonnement(formue):
    
    #Beregner renteindtægt og abonnementomkostning for 1 år baseret på formue.

    #param formue: Kundens formue (Det kan være 100000 for 100.000 kr)
    #return: (tuple) hvor der indgår (renteindtægt, årlige abonnementomkostning)
    
    # Bestem rente og abonnement baseret på formue
    if formue < 10000000:
        årlig_rente = 0.025  # 2.5%
        abonnement_pr_måned = 0  # Gratis
    elif formue <= 250000:
        årlig_rente = 0.0375  # 3.75%
        abonnement_pr_måned = 0  # Gratis
    elif formue <= 500000:
        årlig_rente = 0.05  # 5%
        abonnement_pr_måned = 50  # 50 kr pr måned
    else:
        årlig_rente = 0.05  # 5%
        abonnement_pr_måned = 100  # 100 kr pr måned

    # Beregn renteindtægt
    renteindtægt = formue * årlig_rente
    
    # Beregn årlige abonnementomkostning
    årlige_abonnementomkostning = abonnement_pr_måned * 12
    
    return renteindtægt, årlige_abonnementomkostning

# Eksempel på brug
formue = float(input("Indtast kundens formue: "))

renteindtægt, årlige_abonnementomkostning = beregn_renteindtægt_og_abonnement(formue)
print(f"Renteindtægten for 1 år er: {renteindtægt} kr")
print(f"Årlige abonnementomkostning er: {årlige_abonnementomkostning} kr")