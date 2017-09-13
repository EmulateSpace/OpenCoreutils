/*
 * xmalloc.c
 *
 * (C) 2017.09 <buddy.zhang@aliyun.com>
 *
 * The GNU C Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the GNU C Library; if not, see
 * <http://www.gnu.org/licenses/> 
 */
#include <stdio.h>
#include <stdlib.h>

#include <xmalloc.h>

void *xmalloc(size_t size)
{
    void *alloc = malloc(size);

    if (!alloc) {
        printf("out of memory(malloc)\n");
        exit(EXIT_FAILURE);
    }
    return alloc;
}

void xfree(void *p)
{
    free(p);
}
