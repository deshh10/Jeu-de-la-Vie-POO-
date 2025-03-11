#ifndef CELL_HPP
#define CELL_HPP

class Cell {
public:
    virtual bool isAlive() const = 0;
    virtual void updateState(int neighbors) = 0;
    virtual ~Cell() = default;
};

class NormalCell : public Cell {
private:
    bool state;

public:
    NormalCell(bool alive = false);
    bool isAlive() const override;
    void updateState(int neighbors) override;
};

class ObstacleCell : public Cell {
public:
    bool isAlive() const override;
    void updateState(int neighbors) override;
};

#endif
