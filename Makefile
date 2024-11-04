CC=gcc
CFLAGS=-I.
DEPS = avl_api.h hash_api.h
SRCS            = avl_api.c hash_api.c id_mgmt_app.c
OBJS            = $(SRCS:.c=.o)
IDMGMT          = idMgmt

SRCS1           = avl_api.c hash_api.c utest_id_mgmt.c
OBJS1           = $(SRCS1:.c=.o)
UTESTIDMGMT     = unittest_idMgmt

%.o: %.c $(DEPS)
        $(CC) -c -o $@ $< $(CFLAGS)

all:  $(IDMGMT) $(UTESTIDMGMT)

$(IDMGMT): $(OBJS)
        $(CC) -o $@ $^ $(CFLAGS)

$(UTESTIDMGMT): $(OBJS1)
        $(CC) -o $@ $^ $(CFLAGS)
