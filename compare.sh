cp test.seal std-output/test.seal
./cgen test.seal
test/cgen std-output/test.seal
diff test.s std-output/test.s