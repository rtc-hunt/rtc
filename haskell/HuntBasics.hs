import Control.Monad
import Data.List
import Data.Maybe
import Data.Ord
import Debug.Trace
import qualified Data.Set as Set


isword :: String -> IO Bool
isword a = do {
	file<-readFile "/usr/share/dict/words";
	return $ elem a $ lines file;
	}

mkisword :: IO (String->Bool)
mkisword = do {
	file <- readFile "/usr/share/dict/words";
	let dict = Set.fromList $ words file in
	return (\a->Set.member a dict);
	}

data Trie = Trie Bool ![(Char,Trie)] deriving (Eq, Read, Show)
trieAdd (Trie _ nexts) [] = Trie True nexts
trieAdd (Trie term nexts) (c:rest)
	| (Just a) <- match = Trie term $ (c, trieAdd (snd a) rest) : delete a nexts
	| match == Nothing = Trie term $ (c, trieAdd (Trie False []) rest) : nexts
	where match = find (\(a,_)->a==c) nexts

possibleNexts t str
	| match == Nothing = []
	| (Just (Trie _ pairs)) <- match = map fst pairs
	where match = trieSeek t str

canContinue t str
	| match == Nothing = False
	| (Just _) <- match = True
	where match = trieSeek t str

alternating :: Trie -> String -> [String] -> [[String]]
alternating _ [] q = [q]
--alternating (Trie False _) [] q = []
alternating c (s:str) lsts = nub $
	 do	i<-lsts
		let j=delete i lsts
		let q=i ++ [s]
		guard $ canContinue c q
		alternating c str (q:j)

alternatingWords c s = filter (all (tisWord c)) $ alternating c s ["",""]
--Use: map q $ words "Breclosteont scitortey"

trieSeek a [] = Just a
trieSeek (Trie _ nexts) (c:more)
	| match == Nothing = Nothing
	| (Just a) <- match = trieSeek a more
	where match = lookup c nexts

tisWord (Trie b _) [] = b
tisWord (Trie _ nexts) (c:more)
	| match == Nothing = False
	| (Just a) <- match = tisWord a more
	where match = lookup c nexts

mktrieword :: IO Trie
mktrieword = do {
	file <- readFile "/usr/share/dict/words";
	return $ foldl (\b->(\a-> traceShow a $  trieAdd b a)) (Trie False []) $ words file
	}

sortedWordlist = do {
	file <- readFile "/usr/share/dict/words";
	return $ groupBy (\a->(\b->length a == length b)) $ sortBy (comparing length) $ words file;
}

possibleWords a swl =
	do {
		b <- swl;
		guard (length a==(length $ head b));
		filter (consistentAssignment a) b;
		}

consistentAssignment a b =
	let  thing = map fst $ nub $ zip a b 
	in length thing == (length $ nub thing)
		
cryptog [] _ = [[]]
cryptog inp@(a:b) words = 
	do {
		replacement <- (possibleWords a words);
		rest <- cryptog b words;
		guard (consistentAssignment (concat inp) (concat $ replacement:rest));
		return (replacement:rest);
		}


chooseN :: (Integral b, Eq a) => b -> [a] -> [[a]]
chooseN _ [] = [[]]
chooseN 0 _ = [[]]
chooseN n list =
	do {
		a <- list;
		b <- chooseN (n-1) (delete a list);
		return (a:b);
	}

cryptogramMappings _ [] a _ = a
cryptogramMappings test (word:words) soFarList remaining
		= traceShow ("cryptogMappings",word:words,soFarList,remaining) $ do {
			soFar <- soFarList;
			wordFragment <- [nub (word \\ (map fst soFar))];
			newWord<-chooseN (length wordFragment) remaining;
			newSoFar<-[(zip wordFragment newWord) ++ soFar];
			guard $ test $ map (\a -> fromJust $ lookup a newSoFar) word;
			traceShow (newSoFar) $ cryptogramMappings test words [newSoFar] (remaining \\ newWord);
			}

cryptogram test words =
	do {
		mapping <- cryptogramMappings test (reverse $ sortBy (comparing length) words) [[]] ['a'..'z'];
		return $ map (map (\a->fromJust $ lookup a mapping)) words;
	}

{-
cryptogramD :: String -> String -> String -> [String]
cryptogramD visited alph str =
	do {
		
		a<-alph;

	map str (permutations ['a'..'z'])
	where assignOrder = nub str
	-}
