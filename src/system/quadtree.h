#ifndef QUADTREE_H
#define QUADTREE_H

#include "../math/vec.h"
#include "../config.h"

typedef struct
{
  Vec2i pos;
  void* data;
} QT_Node;

QT_Node* qt_node_create(Vec2i pos, void* data);
void qt_node_destroy(QT_Node* node);

typedef struct _QT QT;
struct _QT
{
  QT_Node* node;

  Vec2i top_left;
  Vec2i bottom_right;

  QT* t_left;
  QT* t_right;
  QT* b_left;
  QT* b_right;
};

QT* qt_create(Vec2i top_left, Vec2i bottom_right);
void qt_destroy(QT* qt);

void qt_print(QT* qt);

void qt_insert(QT* qt, QT_Node* node);
QT_Node* qt_find(QT* qt, Vec2i pos);

#endif
