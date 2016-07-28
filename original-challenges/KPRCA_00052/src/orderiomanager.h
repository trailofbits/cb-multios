#ifndef ORDERIOMANAGER_H_
#define ORDERIOMANAGER_H_

#include "order.h"
#include "iomanager.h"

class OrderIoManager : public IoManager
{
private:
    List<Order> orders;
    void list_orders(); //Lists order + order name
public:
    OrderIoManager();
    virtual ~OrderIoManager();
    bool input_order(size_t idx=-1);
    bool update_order();
    bool delete_order();
    void clear_all_orders(bool force=false);
    bool view_single_order();
    void print_orders(); //List order, pizza info, and everything else
};

#endif
