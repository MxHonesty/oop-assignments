#pragma once
#include "../domain/oferta.h"
#include "../repo/RepoOferta.h"

/** Clasa abstracta responsabila pentru functionlitatea de Undo. */
class UndoAction {
public:
	/** Metoda care executa actiunile necesare de reverse pentru undo. */
	virtual void doUndo() = 0;

	virtual ~UndoAction() = default;
};

/** Undo aferent adaugarii. */
class UndoAdauga: public UndoAction {
protected:
	Oferta oferta_adaugata;  // Obiectul care a fost adaugat.
	Repository* repo;  // Repo in care a fost executata actiunea.
	Cos& cos;

public:
	UndoAdauga(Repository* r, const Oferta& added, Cos& c) : repo{ r }, oferta_adaugata{ added }, cos{c} {}

	/** Elimina elementul adaugat din repo si din cos. Daca acesta nu era in cos inainte, nu se intampla nimic. */
	void doUndo() override {
		repo->remove(oferta_adaugata.get_id());
		cos.sterge(oferta_adaugata);
	}

};

/** Undo aferent stergerii. */
class UndoSterge : public UndoAction {
protected:
	Oferta oferta_stearsa;
	Repository* repo;

public:
	UndoSterge(Repository* r, const Oferta& stearsa) : repo{ r }, oferta_stearsa{ stearsa } {}

	/** Adauga inapoi in repo elementul sters. */
	void doUndo() override {
		repo->add(oferta_stearsa);
	}
};

/** Undo aferent modificarii. */
class UndoModifica : public UndoAction {
protected:
	Oferta oferta_modificata;  // Oferta originala.
	Oferta noua_oferta;  // Oferta de dupa modificare.
	Repository* repo;

public:
	UndoModifica(Repository* r, const Oferta& inainte, const Oferta& dupa) : repo{ r }, oferta_modificata{ inainte }, noua_oferta{ dupa } {};

	/** Modifica obiectul la starea lui originala. */
	void doUndo() override {
		repo->update(noua_oferta.get_id(), oferta_modificata);
	}
};

/** Undo pentru stergere cand elementul sters era si in cos. */
class UndoStergeCuCos : public UndoSterge {
protected:
	Cos& cos;

public:
	UndoStergeCuCos(Repository* r, const Oferta& stearsa, Cos& c) : UndoSterge{ r, stearsa }, cos{ c } {}

	/** Adauga elementul inapoit in repo si cos. */
	void doUndo() override {
		repo->add(oferta_stearsa);
		cos.adauga(oferta_stearsa);
	}

};

/** Undo pentru modificarea cand elementul modificat era si in cos. */
class UndoModificaCuCos : public UndoModifica {
protected:
	Cos& cos;

public:
	UndoModificaCuCos(Repository* r, const Oferta& inainte, const Oferta& dupa, Cos& c) : UndoModifica{ r, inainte, dupa }, cos{ c } {}

	/** Modifica atat in repo cat si in cos. */
	void doUndo() override {
		repo->update(noua_oferta.get_id(), oferta_modificata);
		cos.modifica(noua_oferta, oferta_modificata);
	}
};
