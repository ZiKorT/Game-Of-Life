#ifndef STATE_H
#define STATE_H

#include <memory>

// Classe de base
class CellState {
public:
    virtual ~CellState() = default;
    virtual bool estVivant() const = 0;//Pour connaitre son état
    virtual char symbole() const = 0;//Pour afficher dans la console (1,0)
    virtual std::unique_ptr<CellState> clone() const = 0;//Pour dupliquer une cellule (obligé psk sinon on copie le pointeur)
};

//Classe vivante
class AliveState : public CellState {
public:
    bool estVivant() const override;
    char symbole() const override;
    std::unique_ptr<CellState> clone() const override;
};

//Classe morte
class DeadState : public CellState {
public:
    bool estVivant() const override;
    char symbole() const override;
    std::unique_ptr<CellState> clone() const override;
};


#endif