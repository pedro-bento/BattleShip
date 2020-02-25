#include <stdlib.h>

#include "quadtree.h"
#include "stacktrace.h"

int  qt_inBoundary(QT* qt, Vec2 p);

QT_Node* qt_node_create(Vec2 pos, void* data)
{
  QT_Node* node = malloc(sizeof(QT_Node));
  trace_assert(node);
  node->pos = pos;
  node->data = data;
  return node;
}

void qt_node_destroy(QT_Node* node)
{
  free(node);
}

QT* qt_create(Vec2 top_left, Vec2 bottom_right)
{
  QT* qt = malloc(sizeof(QT));
  trace_assert(qt);
  qt->t_left = NULL;
  qt->t_right = NULL;
  qt->b_left = NULL;
  qt->b_right = NULL;
  qt->node = NULL;
  qt->top_left = top_left;
  qt->bottom_right = bottom_right;
  return qt;
}

void qt_destroy(QT* qt)
{
  if(qt == NULL) return;
  else
  {
    qt_destroy(qt->t_left);
    qt_destroy(qt->t_right);
    qt_destroy(qt->b_left);
    qt_destroy(qt->b_right);
    qt_node_destroy(qt->node);
    free(qt);
  }
}

void qt_insert(QT* qt, QT_Node* node)
{
  if(node == NULL) return;
  if(!qt_inBoundary(qt, node->pos)) return;

  // cannot subdivide
  if(abs(qt->top_left.x - qt->bottom_right.x) <= 1 &&
     abs(qt->top_left.y - qt->bottom_right.y) <= 1)
  {
    if(qt->node == NULL) qt->node = node;
    return;
  }

  if((qt->top_left.x + qt->bottom_right.x) / 2 >= node->pos.x)
  {
    // t_left tree
    if((qt->top_left.y + qt->bottom_right.y) / 2 >= node->pos.y)
    {
      if(qt->t_left == NULL)
      {
        qt->t_left = qt_create(qt->top_left,
          vec2((qt->top_left.x + qt->bottom_right.x) / 2,
               (qt->top_left.y + qt->bottom_right.y) / 2));
      }
      qt_insert(qt->t_left, node);
    }

    // b_left tree
    else
    {
      if(qt->b_left == NULL)
      {
        qt->b_left = qt_create(
          vec2(qt->top_left.x, (qt->top_left.y + qt->bottom_right.y) / 2),
          vec2((qt->top_left.x + qt->bottom_right.x) / 2, qt->bottom_right.y));
      }
      qt_insert(qt->b_left, node);
    }
  }

  else
  {
    // t_right tree
    if((qt->top_left.y + qt->bottom_right.y) / 2 >= node->pos.y)
    {
      if(qt->t_right == NULL)
      {
        qt->t_right = qt_create(
          vec2((qt->top_left.x + qt->bottom_right.x) / 2, qt->top_left.y),
          vec2(qt->bottom_right.x, (qt->top_left.y + qt->bottom_right.y) / 2));
      }
      qt_insert(qt->t_right, node);
    }

    // b_right tree
    else
    {
      if(qt->b_right == NULL)
      {
        qt->b_right = qt_create(
          vec2((qt->top_left.x + qt->bottom_right.x) / 2,
            (qt->top_left.y + qt->bottom_right.y) / 2),
          qt->bottom_right);
      }
      qt_insert(qt->b_right, node);
    }
  }
}

QT_Node* qt_find(QT* qt, Vec2 pos)
{
  if(!qt_inBoundary(qt, pos)) return NULL;
  if(qt->node != NULL) return qt->node;

  if((qt->top_left.x + qt->bottom_right.x) / 2 >= pos.x)
  {
    // t_left tree
    if((qt->top_left.y + qt->bottom_right.y) / 2 >= pos.y)
    {
      if(qt->t_left == NULL)
        return NULL;
      return qt_find(qt->t_left, pos);
    }

    // b_left tree
    else
    {
      if(qt->b_left == NULL)
        return NULL;
      return qt_find(qt->b_left, pos);
    }
  }

  else
  {
    // t_right tree
    if((qt->top_left.y + qt->bottom_right.y) / 2 >= pos.y)
    {
      if(qt->t_right == NULL)
        return NULL;
      return qt_find(qt->t_right, pos);
    }

    // b_right tree
    else
    {
      if(qt->b_right == NULL)
        return NULL;
      qt_find(qt->b_right, pos);
    }
  }
  
  return NULL;
}

int  qt_inBoundary(QT* qt, Vec2 p)
{
  return p.x >= qt->top_left.x && p.x <= qt->bottom_right.x
      && p.y >= qt->top_left.y && p.y <= qt->bottom_right.y;
}
