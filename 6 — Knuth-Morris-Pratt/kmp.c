#include <stdio.h>
#include <stdlib.h>

/* Returns the pointer to the string and writes the its size in *dim */
char *read_text(int *dim)
{
	int size = 2, i = 0;
	char *s = malloc(size * sizeof(char)), t;

	while(( t = getchar() ) != '\n') {
		if(t > 126 || t < 33)
			continue;

		if(++i >= size) {
			size *= 2;
			s = realloc(s, size * sizeof(char));
		}
		*(s + i - 1) = t;
	}

	s = realloc(s, i * sizeof(char) + 1);
	*(s + i + 1) = '\0';
	*dim = i;
	return s;
}


int main() {
    int n, m, *LSP, j = 0;
    char *text, pattern;

    printf("Insert text: ");
    text = read_text(&n);

    printf("Insert pattern: ");
    pattern = read_text(&m);

    /* Build LSP */
    LSP = calloc(m, sizeof(int));
    LSP[0] = 0;

    for (int i = 1; i < m; i++) {
        j = LSP[i - 1];
        while(j > 0 && pattern[i] != pattern[j])
            j = LSP[j - 1];
        if(pattern[i] == pattern[j])
            j++;
        LSP[i] = j;
    }

    /* Match */
    j = 0;
    for(int i = 0; i < n; i++) {
        while(j > 0 && text[i] != pattern[j])
            j = LSP[j - 1];
        if(text[i] == pattern[j]) {
            j++;
            if(j == m)
                printf("Match at offset %d\n", i - j + 1);
        }
    }

    return 0;
}
