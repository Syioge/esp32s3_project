
set(src_dirs 
            IIC
            AT24C02) 
set(include_dirs 
            IIC 
            AT24C02) 
set(requires 
            driver) 

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS  
                        ${include_dirs} REQUIRES ${requires}) 