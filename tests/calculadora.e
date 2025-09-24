class CALCULADORA  -- Identificador: nombre de clase
inherit ANY          -- Herencia de la clase base por defecto

feature         -- Sección de métodos y atributos

    -- Identificador: atributo entero
    contador: INTEGER

    -- Identificador: atributo real
    resultado: REAL

    -- Procedimiento principal
    ejecutar
        local
            x, y: INTEGER      -- Identificadores de variables
            texto: STRING
        do
            -- Asignación de valores (constantes numéricas e identificadores)
            x := 10
            y := 3
            resultado := 0.0
            texto := "Comenzando el cálculo..."  -- Constante de cadena
            io.put_string (texto + "%N")        -- Uso del operador + para concatenar

            -- Ejemplo de estructura condicional
            if x > y then
                io.put_string ("x es mayor que y%N")
            else
                io.put_string ("x no es mayor que y%N")
            end

            -- Ejemplo de bucle con from ... until ... loop
            from
                contador := 0
            until
                contador >= y
            loop
                resultado := resultado + (x / y) * contador
                contador := contador + 1
            end

            -- Mostrar resultados
            io.put_string ("Resultado final = " + resultado.out + "%N")
        end

end  -- Fin de la clase
