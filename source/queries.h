/*
 * Copyright (C) 2016 William Mann
 * This file is part of the "Irrlicht Project" application.
 */

#ifndef QUERIES_H
#define QUERIES_H

#define GET_FILES               "SELECT * FROM files WHERE ID = "

#define GET_CHARACTER           "SELECT * FROM characters WHERE ID = "

#define GET_IRRLICHT_SETTINGS   "SELECT * FROM irrlicht WHERE ID = "

#define GET_LAST                "SELECT * FROM last WHERE ID = "

#define GET_PROPERTIES          "SELECT * FROM properties WHERE ID = "

#define UPDATE_PROPERTIES       "UPDATE properties SET LAST_ACCESSED = datetime(CURRENT_TIMESTAMP, 'localtime') WHERE ID = "

#endif // QUERIES_H
