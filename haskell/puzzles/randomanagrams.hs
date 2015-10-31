import Factory.Math.Implementations.Factorial
import Factory.Data.PrimeFactors
import Debug.Trace

kth k ms = fst $ ms!!k

dropNth :: Int -> [(a, Int)] -> [(a, Int)]
dropNth 0 ((c, 1):ms) = ms
dropNth 0 ((c, n):ms) = (c, (n-1)):ms
dropNth k (hd:ms) = hd:(dropNth (k-1) ms)


--countPermutations ms = (fact (length ms)) / (foldl (*) 1 (map (fact . snd) ms))
countPermutations :: [(a, Int)] -> Int
countPermutations ms = fromIntegral $ product' (recip 5) 10 $ fst $ (primeFactors (foldl (+) 0 $ map snd ms)) >/< (foldl (>*<) (primeFactors 1) (map (primeFactors . snd) ms))

permutationN :: ([(a,Int)]->Int) -> Int -> Int -> Int -> [(a, Int)] -> [a]
permutationN _ 1 _ _ multis = concat [replicate b a|(a,b)<-multis]
permutationN counter n k a multis = let 
                rva = a + (counter $ dropNth k multis)
        in      if (rva < n)
                then permutationN counter n (k+1) rva multis
                else (kth k multis) : permutationN counter (n-a) 0 0 (dropNth k multis)

-- permutationN countPermutations (2896836569686226+1) 0 0 $ map (\a->(head a, length a)) $ group $ sort "ACCCCEGIILMMOOOORSTWY"
-- "CLOWESCOMICORMAGICTOY"