class FOOBAR
feature
   do
      a := 10
      b := 3.14
      c := 2E10
      if a <= b then
         print ("Cadena con comillas: ""hola"" y salto %N")
      else
         -- comentario hasta fin de línea
         b := b / (a - 1)
      end
   end
end
