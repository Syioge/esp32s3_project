
set(src_dirs 
            IIC
            AT24C02
            XL9555) 
set(include_dirs 
            IIC 
            AT24C02
            XL9555) 
set(requires 
            driver
            esp_io_expander
            esp_io_expander_xl9555) 

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS  
                        ${include_dirs} REQUIRES ${requires}) 