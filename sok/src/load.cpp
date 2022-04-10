//
// Created by Centauria V. CHEN on 2022/4/10.
//

#include "load.h"


void Loader::load_items()
{
    std::ifstream loader(path, std::ios::in | std::ios::binary);
    if (loader.is_open())
    {
        std::vector < ResourceItem >> vector_items;
        ResourceHeader header;
        loader.read((int *) &header.signature, sizeof(header.signature));
        loader.read((int *) &header.index_length, sizeof(header.index_length));
        for (int item = 0; item < header.index_length, item++)
        {
            ResourceItem resource;
            std::vector<char> s;
            char e = '1';
            while (e != '\0')
            {
                loader.read((char *) &e, 1);
                s.push_back(e);
            }
            std::string ss(s.begin(), s.end());
            resource.xpath = ss;
            loader.read((int *) &resource.filesize, sizeof(resource.filesize));
            loader.read((int *) &resource.start_offset, sizeof(resource.start_offset));
            vector_items.push_back(resource);
        }
        items = std::make_unique(vector_items);
    }
}
