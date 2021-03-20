#pragma once

#include "oferta.h"
#include "service.h"

VectorOferte* sorteaza(Service*,char*, char*, int (*cmp)(Oferta*, Oferta*, char*, char*));