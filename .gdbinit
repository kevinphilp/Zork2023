set pagination off
set history save on
set history expansion on
set print pretty on

define dump_obj
  set $i=0
  set $m=END_OBJ
  while ($i < $m)
    p objects[$i++]
  end
end

define hero_bag
  p *(struct object_s*)(struct node_t*)(*(*objects[HERO].bag)->head->next)->data
  p *(struct object_s*)(struct node_t*)(*(*objects[HERO].bag)->head->next->next)->data
end
